/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:24:07 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 16:58:24 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fdin_first(t_node *data)
{
	while (data)
	{
		close(data->fdin);
		data = data->next;
	}
}

void	first_child(t_minishell *shell, t_node *data, char **env)
{
	manage_sig();
	handle_redir(shell, data);
	close(shell->pipes[0]);
	if (data->fdout == 1)
		data->fdout = shell->pipes[1];
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
	exit_first_child(data, shell);
}

void	first_exec(t_minishell *shell, t_node *data)
{
	char	**env;

	env = NULL;
	data->pid = fork();
	if (data->pid == 0)
		first_child(shell, data, env);
	close(shell->pipes[1]);
	close_fd(data);
}
