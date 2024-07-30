/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:04:20 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 12:32:11 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_variable(char *token, int *index)
{
	char	*variable;

	variable = NULL;
	if (token[*index + 1] == '{')
	{
		variable = extract_variables_within_braces(&token[*index]);
	}
	else
	{
		variable = extract_variables_without_braces(&token[*index]);
	}
	return (variable);
}

char	*allocate_and_concatenate_result(char *leading_spaces, char *variable,
		char *trailing_spaces)
{
	char	*result;

	result = (char *)malloc(ft_strlen(leading_spaces) + ft_strlen(variable)
			+ ft_strlen(trailing_spaces) + 1);
	if (result)
	{
		ft_strcpy(result, leading_spaces);
		ft_strcat(result, variable);
		ft_strcat(result, trailing_spaces);
	}
	return (result);
}

static char	*handle_variable_expansion(char *token, int *i)
{
	char	*variable;
	char	*leading_spaces;
	char	*trailing_spaces;
	char	*result;

	variable = extract_variable(token, i);
	if (variable)
	{
		leading_spaces = strndup(token, *i);
		trailing_spaces = strdup(token + *i + strlen(variable));
		result = allocate_and_concatenate_result(leading_spaces, variable,
				trailing_spaces);
		free(leading_spaces);
		free(trailing_spaces);
		free(variable);
		return (result);
	}
	return (NULL);
}

char	*expand_variables(char *token)
{
	int	i;
	int	in_single_quotes;

	i = -1;
	in_single_quotes = 0;
	while (token[++i])
	{
		in_single_quotes = is_in_single_quotes(in_single_quotes, token[i]);
		if (should_expand_variable(token, i) && !in_single_quotes)
		{
			return (handle_variable_expansion(token, &i));
		}
	}
	return (extract_variables_from_single_quotes(token));
}
