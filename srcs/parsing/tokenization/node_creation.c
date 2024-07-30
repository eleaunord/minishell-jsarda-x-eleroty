/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:30:30 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 13:33:36 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(char *token)
{
	t_node	*new_node;

	new_node = (t_node *)calloc(1, sizeof(t_node));
	if (!new_node)
	{
		perror("Failed to allocate memory for new node");
		exit(EXIT_FAILURE);
	}
	new_node->content = ft_strdup(token);
	if (!new_node->content)
	{
		free(new_node);
		perror("Failed to duplicate token string");
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_node **tokens_list, char *token)
{
	t_node	*new_node;
	t_node	*current;

	new_node = create_node(token);
	if (!new_node)
		return ;
	if (*tokens_list == NULL)
		*tokens_list = new_node;
	else
	{
		current = *tokens_list;
		while (current->next != NULL)
		{
			if (current->next == *tokens_list)
			{
				perror("Detected circular reference in the list");
				free(new_node->content);
				free(new_node);
				exit(EXIT_FAILURE);
			}
			current = current->next;
		}
		current->next = new_node;
	}
}

void	process_segment(char *start, t_node **tokens_list)
{
	char	*trimmed;
	char	*collapsed;
	char	*segment;

	trimmed = trim_whitespace(start);
	collapsed = collapse_spaces(trimmed);
	segment = ft_strdup(collapsed);
	if (!segment)
	{
		perror("Failed to duplicate segment");
		return ;
	}
	append_node(tokens_list, segment);
	free(segment);
}
