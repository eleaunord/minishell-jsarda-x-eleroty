/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:35:22 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/31 17:26:04 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->cmd = NULL;
	token->args = NULL;
	token->key_expansion = NULL;
	token->type = type;
	token->next = NULL;
	token->processed = 0;
	token->sq = 0;
	return (token);
}

void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}

t_token	*tokenize_input(char *node)
{
	t_token	*tokens;
	int		length;
	int		i;

	tokens = NULL;
	i = 0;
	length = ft_strlen(node);
	while (i < length)
	{
		if (node[i] == '>' || node[i] == '<')
		{
			i = special_tokens(node + i, &tokens, i);
		}
		else
		{
			i = word_token(node, &tokens, i);
		}
	}
	
	return (tokens);
}
