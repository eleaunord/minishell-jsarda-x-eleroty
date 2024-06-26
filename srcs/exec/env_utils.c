/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:06 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/26 12:42:34 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_key(t_env *env, char *key)
{
	int		index;
	t_env	*start;

	index = 0;
	start = env;
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (index);
		env = env->next;
		if (env == start)
			break ;
		index++;
	}
	return (-1);
}

char	*get_path_value(t_minishell *data, char *key)
{
	int		index;
	t_env	*env;
	int		i;

	i = 0;
	env = data->env;
	index = get_key(env, key);
	if (index == -1)
		return (NULL);
	while (i < index)
	{
		env = env->next;
		i++;
	}
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

char	**create_char_env(t_env *env)
{
	t_env	*temp_env;
	char	**dest;
	int		i;

	i = -1;
	if (!env)
		return (NULL);
	dest = malloc(sizeof(char *) * (get_env_list_size(env) + 1));
	if (!dest)
		return (NULL);
	temp_env = env;
	while (++i < get_env_list_size(env))
	{
		dest[i] = ft_strdup(temp_env->str);
		if (!dest[i])
		{
			while (i > 0)
				free(dest[--i]);
			return (free(dest), NULL);
		}
		temp_env = temp_env->next;
	}
	dest[i] = NULL;
	return (dest);
}

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
