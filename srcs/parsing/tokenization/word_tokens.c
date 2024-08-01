/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:36:26 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 11:53:27 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void	tokenize_word(char *input, t_token **tokens, int index,
		int word_start)
{
	int		word_end;
	char	*temp_line;

	word_end = index;
	temp_line = ft_strndup(input + word_start, word_end - word_start);
	if (temp_line)
	{
		add_token_to_list(tokens, new_token(TOKEN_WORD, temp_line));
		free(temp_line);
	}
}

static int	handle_quotes_and_whitespace(char *input, int index, int *in_quotes)
{
	while (input[index] != '\0')
	{
		if (input[index] == '\'' || input[index] == '\"')
		{
			*in_quotes = !*in_quotes;
		}
		if (!*in_quotes && (input[index] == ' ' || input[index] == '>'
				|| input[index] == '<'))
		{
			break ;
		}
		index++;
	}
	return (index);
}

int	word_token(char *input, t_token **tokens, int index)
{
	int in_quotes = 0;
	int word_start = index;

	// Handle initial quotes and whitespace
	index = handle_quotes_and_whitespace(input, index, &in_quotes);
	if (index > word_start)
	{
		tokenize_word(input, tokens, index, word_start);
	}

	// Skip any remaining whitespace
	while (input[index] == ' ')
	{
		index++;
	}
	return (index);
}