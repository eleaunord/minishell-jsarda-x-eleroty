/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:02:40 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 16:24:07 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_variables_within_braces(const char *token)
{
	int	start;
	int	end;

	start = 0;
	end = start + 1;
	while (token[end] && token[end] != '}')
	{
		end++;
	}
	if (token[end] == '}')
	{
		end++;
		return (ft_strsub(token, start, end - start));
	}
	return (NULL);
}

char	*extract_variables_without_braces(const char *token)
{
	int	start;
	int	end;

	start = 0;
	end = start + 1;
	while (token[end] && (is_alpha_underscore(token[end]) || token[end] == '?'))
		end++;
	return (ft_strsub(token, start, end - start));
}

char	*extract_var_from_single_quotes(const char *token)
{
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{
		return (NULL);
	}
	return (ft_strdup(token));
}

char	*extract_variable_name(char *trim, char *str, int *i)
{
	while (str && str[*i] && str[*i] != ' ' && check_expand_name(str[*i])
		&& str[*i] != '$')
		trim = ft_realloc(trim, str[(*i)++], 0);
	if (str[*i] == '$' || str[*i] == ' ' || !check_expand_name(str[*i]))
		(*i)--;
	return (trim);
}
