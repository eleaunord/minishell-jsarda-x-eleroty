/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:52:13 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 12:52:25 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_heredocs(t_token **tokens, t_node *node)
{
	t_token	*current;
	int		i;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	i = 0;
	while (current)
	{
		if (current->type == HEREDOC_TOKEN)
		{
			node->is_here_doc = 1;
			if (current->next && current->next->type == TOKEN_WORD)
			{
				i++;
			}
		}
		current = current->next;
	}
	node->limiter_hd_count = i;
}

void	allocate_memory_for_limiter_hd(t_node *node)
{
	int	i;

	node->limiter_hd = (char **)calloc(node->limiter_hd_count + 1,
			sizeof(char *));
	if (!node->limiter_hd)
	{
		perror("calloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < node->limiter_hd_count)
	{
		node->limiter_hd[i] = NULL;
		i++;
	}
	node->limiter_hd[i] = NULL;
}

void	process_heredoc_tokens(t_token *tokens, t_node *node)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == HEREDOC_TOKEN && current->next
			&& current->next->type == TOKEN_WORD)
		{
			if (i < node->limiter_hd_count)
			{
				node->limiter_hd[i++] = ft_strdup(current->next->value);
			}
			current->next->processed = 1;
		}
		current = current->next;
	}
}
