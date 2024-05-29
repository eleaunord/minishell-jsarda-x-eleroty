/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:06 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/29 14:51:44 by jsarda           ###   ########.fr       */
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
