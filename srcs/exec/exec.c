/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:09:00 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/18 16:47:24 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_fd(t_node *node)
{
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
}

void	exec(t_node *list, t_minishell *data)
{
	int		i;

	init_fd(list);
	i = 0;
	if (list->here_doc)
	{
		while (list->limiter_hd[i])
		{
			heredoc(list->limiter_hd[i], list->heredoc_filename);
			i++;
		}
	}
	// if (list->next != NULL)
	// 	exec_pipe(list);
	// else
	exec_simple_cmd(data, list);
}
