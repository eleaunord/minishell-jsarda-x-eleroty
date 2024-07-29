/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:41:13 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:41:23 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_first_child(t_node *data, t_shell *shell)
{
	if (!data->cmd)
	{
		close(shell->pipes[1]);
		free_child(data, shell, 0);
		exit(0);
	}
	close(shell->pipes[1]);
	free_child(data, shell, 0);
	exit(127);
}

void	exit_other_child(t_node *data, t_shell *shell)
{
	if (!data->cmd)
	{
		free_child(data, shell, 0);
		exit(1);
	}
	free_child(data, shell, 0);
	if (errno == 13)
		exit(126);
	exit(127);
}

void	manager_mid(t_node *data, t_shell *shell, int fd_tmp)
{
	if (data->fdin == 0 || data->fdin == -1)
		data->fdin = fd_tmp;
	if (data->fdout == 1 || data->fdout == -1)
	{
		close(shell->pipes[0]);
		data->fdout = shell->pipes[1];
	}
}

void	close_fd(t_node *data)
{
	if (data->fdin != -1 && data->fdin != 0)
		close(data->fdin);
	if (data->fdout != -1 && data->fdout != 1)
	{
		if (data->next && data->next->fdout != data->fdout)
			return ;
		close(data->fdout);
	}
}

void	manage_no_path(t_node *head, t_shell *shell, int mod)
{
	ft_errors_exec(1, "command not found", head->cmd, 127);
	head->status = 127;
	if (mod == 0)
		close(shell->pipes[0]);
	else
		close(shell->pipes[1]);
	close_fd(head);
}
