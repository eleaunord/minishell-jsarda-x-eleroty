/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:06 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/29 16:52:46 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
char	**create_char_env(t_env *env)
{
	t_env	*temp_env;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	temp_env = env;
	dest = (char **)malloc(sizeof(char *) * (len_list(temp_env) + 1));
	if (!dest)
		return (NULL);
	dest[i] = (temp_env->str);
	temp_env = temp_env->next;
	i++;
	while (temp_env != env)
	{
		dest[i] = (temp_env->str);
		temp_env = temp_env->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}