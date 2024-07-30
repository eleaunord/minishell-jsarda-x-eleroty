/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:56:53 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 11:57:52 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*duplicate_string(const char *src)
{
	if (src == NULL)
		return (NULL);
	return (ft_strdup(src));
}

static char	*extract_key(const char *src, char *equal_sign)
{
	if (src == NULL || equal_sign == NULL)
		return (NULL);
	return (ft_strndup(src, equal_sign - src));
}

static char	*extract_value(const char *src, char *equal_sign)
{
	if (src == NULL || equal_sign == NULL || equal_sign[1] == '\0')
		return (NULL);
	return (ft_strdup(equal_sign + 1));
}

// Function to parse and assign key and value from an element string
int	parse_key_value(t_env **new, char *elem)
{
	char	*equal_sign;

	equal_sign = ft_strchr(elem, '=');
	if (equal_sign)
	{
		(*new)->key = extract_key(elem, equal_sign);
		if ((*new)->key == NULL)
			return (0);
		(*new)->value = extract_value(elem, equal_sign);
		if ((*new)->value == NULL)
		{
			free((*new)->key);
			(*new)->key = NULL;
			free_var_env(*new);
			return (0);
		}
	}
	else
	{
		(*new)->key = duplicate_string(elem);
		if ((*new)->key == NULL)
			return (0);
		(*new)->value = NULL;
	}
	return (1);
}
