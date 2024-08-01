/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:30:06 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 16:15:51 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_alnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'));
}

int	should_expand_variable(char *token, int index)
{
	return (token[index] == '$' && (is_alnum(token[index + 1]) || token[index
				+ 1] == '_'));
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
