/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:09:00 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/20 11:41:15 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_fd(t_node *node)
{
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
}

void exec(t_node *list, t_minishell *data)
{
	int	i;

	int		stdin_copy;
	int		stdout_copy;
	init_fd(list);
	i = 0;
	if (list->here_doc && list->next == NULL)
	{
		while (list->limiter_hd[i])
		{
			get_tmp_file(list);
			heredoc(list->limiter_hd[i], list->heredoc_filename);
			i++;
			if (list->limiter_hd[i])
				unlink(list->heredoc_filename);
		}
	}
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (list->next != NULL)
		exec_pipe(list, data);
	else
		exec_simple_cmd(data, list);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	unlink(list->heredoc_filename);
}
