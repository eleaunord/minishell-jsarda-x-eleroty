/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:06 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/29 14:59:03 by eleroty          ###   ########.fr       */
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
