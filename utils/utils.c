/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliensarda <juliensarda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:09:37 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/25 09:27:13 by juliensarda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_key_value(t_env *env, char *key)
{
	t_env	*start;
	t_env	*current;

	current = env;
	start = env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (current->value);
		current = current->next;
		if (current == start)
			return (NULL);
	}
	return (NULL);
}

int	check_key(t_env *env, char *key)
{
	t_env	*start;
	t_env	*current;

	current = env;
	start = env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (0);
		current = current->next;
		if (current == start)
			return (1);
	}
	return (1);
}
