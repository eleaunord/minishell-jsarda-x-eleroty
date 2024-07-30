/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:15:58 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/30 18:14:39 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first(t_node *head, t_minishell *shell)
{
	head->path = get_cmd_path(head, shell);
	first_exec(shell, head);
}

void	mid(t_node *head, t_minishell *shell)
{
	head->path = get_cmd_path(head, shell);
	middle_exec(shell, head, shell->pipes[0]);
}

void	last(t_node *head, t_minishell *shell)
{
	head->path = get_cmd_path(head, shell);
	last_exec(shell, head);
}

void	exec_pipe(t_minishell *shell, int nb_cmd)
{
	int		i;
	t_node	*head;

	head = shell->nodes;
	i = -1;
	pipe(shell->pipes);
	if (head->fdintmp != -1)
		first(head, shell);
	else
		close(shell->pipes[1]);
	head = head->next;
	while (++i < (nb_cmd - 2))
	{
		mid(head, shell);
		head = head->next;
	}
	last(head, shell);
	head = shell->nodes;
	ft_wait(head);
	close(shell->pipes[1]);
	close(shell->pipes[0]);
}
