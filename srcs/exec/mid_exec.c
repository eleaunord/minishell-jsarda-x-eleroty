/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:45:52 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:41:18 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_close_fdin_mid(t_node *data)
{
	while (data)
	{
		close(data->fdin);
		data = data->next;
	}
}

void	mid_child(t_shell *shell, t_node *data, char **env, int fd_tmp)
{
	handle_redir(shell, data);
	manager_mid(data, shell, fd_tmp);
	if (data->cmd && is_built_in(data) == -1)
	{
		env = create_char_env(shell->envp, get_env_list_size(shell->envp));
		if (!data->path && data->cmd && is_built_in(data) == -1)
			manage_no_path(data, shell, 1);
		else
		{
			ft_dup(data);
			//ft_close_fdin_mid(data);
			if (execve(data->path, data->args, env) == -1)
				execve_fail();
		}
	}
	else if (is_built_in(data) != -1)
		exec_built_in(data, shell);
	exit_other_child(data, shell);
}

void	middle_exec(t_shell *shell, t_node *data, int fd_tmp)
{
	char	**env;

	env = NULL;
	pipe(shell->pipes);
	data->pid = fork();
	if (data->pid == 0)
	{
		manage_sig();
		mid_child(shell, data, env, fd_tmp);
	}
	close(shell->pipes[1]);
	close(fd_tmp);
	close_fd(data);
}
