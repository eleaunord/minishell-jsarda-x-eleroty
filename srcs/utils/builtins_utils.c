/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:30:23 by juliensarda       #+#    #+#             */
/*   Updated: 2024/07/16 10:18:11 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_value(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strncmp(current->name, key, ft_strlen(current->name)))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	check_key(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strncmp(current->name, key, ft_strlen(current->name)))
			return (0);
		current = current->next;
	}
	return (1);
}
