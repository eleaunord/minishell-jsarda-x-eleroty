/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:36:03 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 13:36:08 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	update_quote_state(char c, bool in_quote, char *quote_char)
{
	if (in_quote && c == *quote_char)
	{
		*quote_char = '\0';
		return (false);
	}
	else if (!in_quote)
	{
		*quote_char = c;
		return (true);
	}
	return (in_quote);
}

char	*trim_leading_spaces(char *str)
{
	while (*str && isspace((unsigned char)*str))
		str++;
	return (str);
}

void	trim_trailing_spaces(char *str)
{
	char	*end;
	bool	in_quote;
	char	quote_char;

	end = str + strlen(str) - 1;
	in_quote = false;
	quote_char = '\0';
	while (end > str)
	{
		if (*end == '\'' || *end == '"')
		{
			in_quote = update_quote_state(*end, in_quote, &quote_char);
		}
		if (!in_quote && isspace((unsigned char)*end))
			end--;
		else
			break ;
	}
	end[1] = '\0';
}

char	*trim_whitespace(char *str)
{
	str = trim_leading_spaces(str);
	if (*str != '\0')
	{
		trim_trailing_spaces(str);
	}
	return (str);
}
