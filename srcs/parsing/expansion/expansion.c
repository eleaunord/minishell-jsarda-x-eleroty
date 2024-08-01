/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:00:47 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 10:33:02 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*construct_result(char *key_expansion, char *start, char *end,
		char *path_value)
{
	size_t	leading_length;
	size_t	key_length;
	size_t	trailing_length;
	size_t	result_length;
	char	*result;

	leading_length = start - key_expansion;
	key_length = ft_strlen(path_value);
	trailing_length = ft_strlen(end);
	result_length = leading_length + key_length + trailing_length;
	result = (char *)malloc(result_length + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, key_expansion);
	result[leading_length] = '\0';
	ft_strcat(result, path_value);
	ft_strcat(result, end);
	return (result);
}

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

// void	process_expansions(t_token **tokens)
// {
// 	t_token	*tok;
// 	int		needs_expansion;

// 	if (!tokens)
// 		return ;
// 	tok = *tokens;
// 	while (tok != NULL)
// 	{
// 		check_needs_expansion(tok, &needs_expansion);
// 		if (needs_expansion)
// 			tok->key_expansion = expand_variables(tok->value);
// 		else
// 			tok->key_expansion = NULL;
// 		tok = tok->next;
// 	}

// }

void	check_is_btw_sq(t_token *tok, int *is_in_single_quotes)
{
	char	*value;
	size_t	len;

	value = tok->value;
	len = strlen(value);
	if (len >= 2 && value[0] == '\'' && value[len - 1] == '\'')
	{
		*is_in_single_quotes = 1;
	}
	else
	{
		*is_in_single_quotes = 0;
	}
}

void	process_expansions(t_token **tokens)
{
	t_token	*tok;
	int		is_in_single_quotes;

	if (!tokens)
		return ;
	tok = *tokens;
	is_in_single_quotes = 0;
	while (tok != NULL)
	{
		check_is_btw_sq(tok, &is_in_single_quotes);
		if (is_in_single_quotes)
			tok->sq = 1;
		else
			tok->sq = 0;
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
