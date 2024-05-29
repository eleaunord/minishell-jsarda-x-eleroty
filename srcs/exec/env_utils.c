/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:06 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/29 17:32:32 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_key(char *key, int env_size, char *key_word)
{
	int	index;

	index = 0;
	printf("%s\n", key);
	while (index < env_size)
	{
		if (ft_strcmp(&key[index], key_word) == 0)
			return (index);
		index++;
	}
	return (-1);
}

char	*get_path_value(t_minishell *data, char *key)
{
	int	index;
	int	env_size;

	env_size = 50;
	// printf("data env key%s\n",data->env->key);
	// printf("%s\n", data->env->key);
	// printf("size of the env%d\n",env_size);
	index = get_key(data->env->key, env_size, key);
	if (index == -1)
		return (NULL);
	return (&data->env->value[index]);
}

int	ft_sizeenv(t_env *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		++counter;
		lst = lst->next;
	}
	return (counter);
}
// Creates a char ** array from the linked list env
char	**create_char_env(t_env *env)
{
	t_env	*temp_env;
	char	**dest;
	int		i;
	int		size;

	if (!env)
		return (NULL);
	size = ft_sizeenv(env);
	dest = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	temp_env = env;
	for (i = 0; i < size; i++)
	{
		dest[i] = ft_strdup(temp_env->str);
			// Duplicate the string to create independent copies
		if (!dest[i])
		{
			while (i > 0)
			{
				free(dest[--i]);
			}
			free(dest);
			return (NULL);
		}
		temp_env = temp_env->next;
	}
	dest[i] = NULL; // Null-terminate the array
	// Print the array for debugging
	for (i = 0; dest[i]; i++)
	{
		printf("%s\n", dest[i]);
	}
	return (dest);
}

// Function to free the allocated char ** array
void	free_char_env(char **env)
{
	int i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}