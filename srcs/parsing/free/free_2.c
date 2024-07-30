/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:29:44 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 14:38:45 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_hd(t_node *node_list)
{
	if (node_list->last_heredoc)
	{
		if (node_list->fdin != -1 && node_list->fdin != 0)
			close(node_list->fdin);
		free(node_list->last_heredoc);
		node_list->last_heredoc = NULL;
	}
}

void	free_files(t_node *node_list)
{
	if (node_list->filename_in)
	{
		freetab(node_list->filename_in);
		node_list->filename_in = NULL;
	}
	if (node_list->filename_out)
	{
		freetab(node_list->filename_out);
		node_list->filename_out = NULL;
	}
	if (node_list->limiter_hd)
	{
		freetab(node_list->limiter_hd);
		node_list->limiter_hd = NULL;
	}
	free_hd(node_list);
	if (node_list->content)
		free(node_list->content);
	if (node_list)
		free(node_list);
	node_list = NULL;
}

void	free_nodes(t_node *node_list)
{
	if (!node_list)
		return ;
	if (node_list->cmd)
	{
		free(node_list->cmd);
		node_list->cmd = NULL;
	}
	if (node_list->path)
	{
		free(node_list->path);
		node_list->path = NULL;
	}
	if (node_list->args)
	{
		freetab(node_list->args);
		node_list->args = NULL;
	}
	if (node_list->tokens_in_node)
		free_tokens(node_list->tokens_in_node);
	free_files(node_list);
}

void	clear_nodes(t_node **node_list)
{
	t_node	*tmp;

	if (!node_list || !*node_list)
		return ;
	while (node_list && *node_list)
	{
		tmp = (*node_list)->next;
		free_nodes(*node_list);
		*node_list = tmp;
	}
}
