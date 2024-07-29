/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:11:03 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:41:12 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_node *data)
{
	while (data)
	{
		if (data->fdin != -1 && data->fdin != 0)
			close(data->fdin);
		if (data->fdout != -1 && data->fdout != 1)
			close(data->fdout);
		data = data->next;
	}
}

int	exec(t_shell *shell)
{
	t_node	*datas;
	int		num_cmd;

	num_cmd = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	datas = shell->datas;
	handle_heredoc(shell, datas);
	open_files(&datas);
	datas = shell->datas;
	if (datas->next != NULL)
	{
		num_cmd = ft_lstsize_cmd(shell->datas);
		exec_pipe(shell, num_cmd);
	}
	else
		exec_simple_cmd(datas, shell);
	ft_close(datas);
	free_hd_file(&(shell->datas), 2);
	free_hd_file(&(shell->datas), 1);
	return (0);
}
