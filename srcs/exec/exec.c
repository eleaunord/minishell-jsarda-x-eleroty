/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliensarda <juliensarda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:09:00 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/17 14:08:16 by juliensarda      ###   ########.fr       */
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
	printf("heredoc filename is%s\n", list->filenames[i]);
	if (list->tokens_in_node->type == HEREDOC_TOKEN)
	{
		while (list->filenames[i])
		{
			heredoc(list->filenames[i]);
			i++;
		}
	}
	// if (list->next != NULL)
	// 	exec_pipe(list);
	// else
		exec_simple_cmd(data, list);
}
