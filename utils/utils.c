/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:09:37 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/26 12:30:27 by jsarda           ###   ########.fr       */
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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	safe_malloc(char **new_tab, t_minishell *data)
{
	ft_error("malloc : ", strerror(errno), 1, data);
	if (new_tab)
		free_tab(new_tab);
}

size_t	count_args(char **args)
{
	size_t	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}
