/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:00:47 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 13:37:28 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_needs_expansion(t_token *tok, int *needs_expansion)
{
	char	*value;

	value = tok->value;
	*needs_expansion = 0;
	while (*value)
	{
		if (*value == '$' && is_alpha_underscore(*(value + 1)))
		{
			*needs_expansion = 1;
			break ;
		}
		value++;
	}
}

void	process_expansions(t_token **tokens)
{
	t_token	*tok;
	int		needs_expansion;

	if (!tokens)
		return ;
	tok = *tokens;
	while (tok != NULL)
	{
		check_needs_expansion(tok, &needs_expansion);
		if (needs_expansion)
			tok->key_expansion = expand_variables(tok->value);
		else
			tok->key_expansion = NULL;
		tok = tok->next;
	}
}

void	check_lonely_expansions(t_token *tokens, t_node *node)
{
	t_token	*tok;
	int		i;

	tok = tokens;
	if (!tokens || !node)
		return ;
	i = 0;
	while (tok && i < 1)
	{
		if (tok->key_expansion != NULL)
			node->lonely_expansion = 1;
		i++;
	}
}
