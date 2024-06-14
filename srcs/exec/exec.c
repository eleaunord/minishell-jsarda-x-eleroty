/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:09:00 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/14 15:10:30 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_fd(t_node *node)
{
	node->fd_in = STDIN_FILENO;   // Initialize to invalid file descriptor
	node->fd_out = STDOUT_FILENO; // Initialize to invalid file descriptor
}

void	exec(t_node *list, t_minishell *data)
{
	char	*path;
	int		i;

	init_fd(list);
	i = 0;
	path = NULL;
	if (list->here_doc)
	{
		while (list->limiter_hd[i])
		{
			heredoc(list->limiter_hd[i], list->filename_in[i]);
			i++;
		}
	}
	if (list->next != NULL)
		exec_pipeline(list, data);
	else
		exec_simple_cmd(data, list, path);
}
