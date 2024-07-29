/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:24:02 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:41:37 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_redir(t_node *datas, t_node *current, t_shell *shell)
{
	if (check_if_redir(datas) == 0 || datas->is_hd == 1)
	{
		while (current)
		{
			handle_redir(shell, datas);
			current = current->next;
		}
	}
}

int	check_and_redir_builtins(t_shell *shell, t_node *datas, t_node *current)
{
	if (check_if_redir(datas) == 0 || datas->is_hd == 1)
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

void	exec_child_process(t_shell *shell, char *path)
{
	t_node	*datas;
	t_node	*current;
	char	**env;

	datas = shell->datas;
	current = datas;
	check_and_redir(datas, current, shell);
	env = create_char_env(shell->envp, get_env_list_size(shell->envp));
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

int	dir_error(char *cmd)
{
	int	tmp;

	if (!cmd)
		return (0);
	tmp = open(cmd, O_DIRECTORY);
	if (tmp > 0)
	{
		ft_errors_exec(1, "Is a directory", cmd, 126);
		close(tmp);
		return (1);
	}
	if (tmp != -1)
		close(tmp);
	return (0);
}

void	exec_simple_cmd(t_node *data, t_shell *shell)
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
	if (dir_error(data->cmd))
		return (free(data->path));
	data->path = get_cmd_path(current, shell);
	if (!data->path && data->cmd)
		return (ft_errors_exec(1, "command not found", data->cmd, 127),
			free(data->path));
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
