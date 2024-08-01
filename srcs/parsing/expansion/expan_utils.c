/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:30:06 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 14:23:25 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_alnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'));
}

int	check_expand_name(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95 || c == '?')
		return (1);
	return (0);
}

int	is_in_sq(int in_single_quotes, char c)
{
	if (c == '\'')
		return (!in_single_quotes);
	return (in_single_quotes);
}

char	*toggle_quote_flags(int *sq, int *dq, char *str, int i)
{
	if (str[i] == '\'' && *sq == 0 && *dq == 1)
		;
	else if (str[i] == '\'' && *sq == 0 && *dq == 0)
		*sq = 1;
	else if (str[i] == '\'' && *sq == 1)
		*sq = 0;
	else if (str[i] == '\"' && *dq == 0 && *sq == 1)
		;
	else if (str[i] == '\"' && *dq == 0 && *sq == 0)
		*dq = 1;
	else if (str[i] == '\"' && *dq == 1)
		*dq = 0;
	return (NULL);
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
