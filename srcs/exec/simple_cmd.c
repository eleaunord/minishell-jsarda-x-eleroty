/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:24:02 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/30 18:12:05 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_redir(t_node *datas, t_node *current, t_minishell *shell)
{
	if (check_if_redir(datas) == 0 || datas->is_here_doc == 1)
	{
		while (current)
		{
			handle_redir(shell, datas);
			current = current->next;
		}
	}
}

int	check_and_redir_builtins(t_minishell *shell, t_node *datas, t_node *current)
{
	if (check_if_redir(datas) == 0 || datas->is_here_doc == 1)
	{
		while (current)
		{
			if (handle_redir_builtins(datas, shell, 0))
				return (1);
			current = current->next;
		}
	}
	return (0);
}

void	exec_child_process(t_minishell *shell, char *path)
{
	t_node	*datas;
	t_node	*current;
	char	**env;

	datas = shell->nodes;
	current = datas;
	check_and_redir(datas, current, shell);
	env = create_char_env(shell->env, get_env_list_size(shell->env));
	ft_dup(datas);
	if (datas->fdin != -1 && datas->fdin != 0)
		close(datas->fdin);
	if (datas->fdout != -1 && datas->fdout != 1)
		close(datas->fdout);
	manage_sig();
	if (path == NULL || execve(path, datas->args, env) == -1)
		perror("execve");
	close_fd(datas);
	free_child(datas, shell, 0);
	free(path);
	exit(0);
}

void	cmd_error(char *cmd)
{
	ft_errors_exec(1, "command not found", cmd, 127);
}

void	exec_simple_cmd(t_node *data, t_minishell *shell)
{
	t_node	*current;

	current = data;
	if (check_if_redir(data) == 0 && data->fdintmp == -1)
		return ;
	if (is_built_in(data) != -1)
	{
		if (!check_and_redir_builtins(shell, data, current))
			exec_built_in(data, shell);
		return ;
	}
	if (directory_error(data->cmd))
		return (free(data->path));
	data->path = get_cmd_path(current, shell);
	if (!data->path && data->cmd)
		return (cmd_error(data->cmd), free(data->path));
	if (!data->cmd)
		return ;
	data->pid = fork();
	if (data->pid < 0)
		perror("fork");
	else if (data->pid == 0)
		exec_child_process(shell, data->path);
	else
		ft_wait(data);
}
