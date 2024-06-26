/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:06 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/10 14:11:54 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// VARIABLE EXPANSION

// char	*get_env_value(const char *name, t_minishell *mini)
// {
// 	t_env	*current;

// 	current = mini->env;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, name) == 0)
// 		{
// 			return (current->value);
// 		}
// 		current = current->next;
// 	}
// 	return (NULL); // Variable not found
// }

int	get_key(t_env *env, char *key)
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
char	*get_path_value(t_minishell *data, char *key)
{
	int		index;
	t_env	*env;

	env = data->env;
	index = get_key(env, key);
	if (index == -1)
		return (NULL);
	for (int i = 0; i < index; i++)
		env = env->next;
	return (env->value);
}

int	get_env_list_size(t_env *list)
{
	int		count;
	t_env	*start;

	count = 0;
	start = list;
	if (!list)
		return (0);
	while (list)
	{
		count++;
		list = list->next;
		if (list == start)
			break ;
	}
	return (count);
}

// Creates a char ** array from the linked list env
char	**create_char_env(t_env *env)
{
	t_env	*temp_env;
	char	**dest;
	int		i;
	int		size;

	i = 0;
	if (!env)
		return (NULL);
	size = get_env_list_size(env);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	temp_env = env;
	while (i < size)
	{
		dest[i] = ft_strdup(temp_env->str);
		if (!dest[i])
		{
			while (i > 0)
				free(dest[--i]);
			return (free(dest), NULL);
		}
		temp_env = temp_env->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

// Function to free the allocated char ** array
void	free_char_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
