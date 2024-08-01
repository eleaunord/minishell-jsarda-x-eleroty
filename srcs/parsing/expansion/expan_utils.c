/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:30:06 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 10:33:42 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_alnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'));
}

int	is_in_sq(int in_single_quotes, char c)
{
	if (c == '\'')
		return (!in_single_quotes);
	return (in_single_quotes);
}

int	should_expand_variable(char *token, int index)
{
	return (token[index] == '$' && (is_alnum(token[index + 1]) || token[index
				+ 1] == '_'));
}

int	count_expansions(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->key_expansion != NULL)
		{
			count++;
		}
		current = current->next;
	}
	return (count);
}

void	set_expansions(t_token *tokens, t_node *node)
{
	int	expansion_count;

	if (!tokens || !node)
		return ;
	expansion_count = count_expansions(tokens);
	node->expansion_count = expansion_count;
}
