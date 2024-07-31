/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:31:05 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/31 18:12:54 by eleroty          ###   ########.fr       */
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
	key = extract_the_key(*start, *end, dollar_pos);
	return (key);
}

// char	*get_expansion(t_minishell *data,  t_token *tok)
// {
// 	char	*start;
// 	char	*end;
// 	char	*key;
// 	char	*path_value;
// 	char *result;
// 	char *str;

// 	str = tok->key_expansion;
// 	int i = 0;
// 	while (str[i])
// 	{
// 		key = extract_key(tok->value, &start, &end);
// 		printf("key : %s\n", key);
// 		path_value = get_path_value(data, key);
// 		printf("path : %s\n", path_value);
// 		free(key);
// 		if (!path_value)
// 			return (NULL);
// 		result = construct_result(tok->value, start, end, path_value);
// 		printf("res : %s\n", result);
// 		i++;
// 	}
// 	return (result);
// }

char	*get_expansion(t_minishell *data, t_token *tok)
{
	char	*start;
	char	*end;
	char	*key;
	char	*path_value;
	char	*result;
	size_t	key_length;
	char	*new_key_expansion;

	// Extract key and get the path value for the key
	key = extract_key(tok->key_expansion, &start, &end);
	printf("key extracted : %s\n", key);
	path_value = get_path_value(data, key);
	// Free the key after use
	free(key);
	printf("path extracted : %s\n", path_value);
	if (!path_value)
		return (NULL);
	printf("path extracted : %s\n", path_value);
	// Construct the result by expanding the key in the token's key_expansion
	result = construct_result(tok->key_expansion, start, end, path_value);
	// Free the path_value after use
	free(path_value);
	if (!result)
		return (NULL);
	// Remove the key and its expansion from tok->key_expansion
	key_length = end - start;
	new_key_expansion = (char *)malloc(strlen(tok->key_expansion) - key_length
			+ 1);
	if (!new_key_expansion)
	{
		free(result);
		return (NULL);
	}
	// Copy the part before the key
	strncpy(new_key_expansion, tok->key_expansion, start - tok->key_expansion);
	// Copy the part after the key
	strcpy(new_key_expansion + (start - tok->key_expansion), end);
	// Free the old key_expansion and set the new one
	free(tok->key_expansion);
	tok->key_expansion = new_key_expansion;
	printf("new key_expansion : %s\n", tok->key_expansion);
	return (result);
}
