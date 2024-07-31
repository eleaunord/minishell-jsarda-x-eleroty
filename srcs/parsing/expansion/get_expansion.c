/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:31:05 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/31 12:30:51 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_the_key(t_env *env, char *key)
{
	int	index;

	index = 0;
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (index);
		env = env->next;
		index++;
	}
	return (-1);
}

char	*extract_the_key(char *start, char *end, char *dollar_pos)
{
	size_t	key_length;
	size_t	offset;

	key_length = end - start;
	if (dollar_pos != NULL)
	{
		offset = 1;
	}
	else
	{
		offset = 0;
	}
	key_length -= offset;
	return (ft_strndup(start + offset, key_length));
}

void	find_key_start_end(char *key_expansion, char **start, char **end)
{
	char	*dollar_pos;

	dollar_pos = ft_strchr(key_expansion, '$');
	if (dollar_pos)
	{
		*start = dollar_pos;
		*end = dollar_pos + 1;
		while (is_alpha_underscore(**end))
			(*end)++;
	}
	else
	{
		*start = key_expansion;
		*end = key_expansion;
		while (is_alpha_underscore(**end))
			(*end)++;
	}
}

static char	*extract_key(char *key_expansion, char **start, char **end)
{
	char	*dollar_pos;
	char	*key;

	find_key_start_end(key_expansion, start, end);
	dollar_pos = ft_strchr(key_expansion, '$');
	// dollar_pos = ft_strchr(*start, '$');
	key = extract_the_key(*start, *end, dollar_pos);
	return (key);
}

char	*get_expansion(t_minishell *data, char *key_expansion)
{
	char	*start;
	char	*end;
	char	*key;
	char	*path_value;
	char	*result;

	key = extract_key(key_expansion, &start, &end);
	path_value = get_path_value(data, key);
	free(key);
	if (!path_value)
		return (NULL);
	result = construct_result(key_expansion, start, end, path_value);
	return (result);
}
