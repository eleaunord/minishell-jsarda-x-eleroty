/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:13:55 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 16:58:28 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fdin(t_node *data)
{
	while (data)
	{
		close(data->fdin);
		close(data->fdintmp);
		data = data->next;
	}
}

void	last_child(t_minishell *shell, t_node *data, char **env)
{
	data->fdin = shell->pipes[0];
	handle_redir(shell, data);
	manage_sig();
	if (data->fdin == 0)
		data->fdin = shell->pipes[0];
	if (data->cmd && is_built_in(data) == -1)
	{
		env = create_char_env(shell->env, get_env_list_size(shell->env));
		if (!data->path && data->cmd && is_built_in(data) == -1)
			manage_no_path(data, shell, 1);
		else
		{
			ft_dup(data);
			if (execve(data->path, data->args, env) == -1)
				execve_fail();
		}
	}
	else if (is_built_in(data) != -1)
		exec_built_in(data, shell);
	exit_other_child(data, shell);
}

void	last_exec(t_minishell *shell, t_node *data)
{
	char	**env;

	env = NULL;
	data->pid = fork();
	if (data->pid == 0)
		last_child(shell, data, env);
	close(shell->pipes[0]);
	close_fd(data);
}
