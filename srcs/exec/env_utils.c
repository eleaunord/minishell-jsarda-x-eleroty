/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:06 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/29 13:29:19 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_key(t_env *env, int env_size, char *key)
{
	int	index;

	index = 0;
	while (index < env_size)
	{
		if (ft_strcmp(env[index].key, key) == 0)
			return (index);
		index++;
	}
	return (-1);
}

char	*get_path_value(t_minishell *data, char *key)
{
	int	index;
	int	env_size;

	env_size = ft_strlen(data->env->key);
	index = get_key(data->env, env_size, key);
	if (index == -1)
		return (NULL);
	return (data->env[index].value);
}
