/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:24:48 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/06 14:47:39 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	modify_value(t_env *current, const char *value)
{
	free(current->value);
	current->value = strdup(value);
	if (!current->value)
		return ;
}

void	create_var(t_minishell *data, const char *key, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("malloc");
		return ;
	}
	new_var->key = strdup(key);
	new_var->value = strdup(value);
	new_var->next = data->env;
	data->env = new_var;
}

void	ft_export(t_minishell *data, char **args)
{
	int		i;
	t_env	*current;
	t_env	*prev;
	char	**var;

	i = 0;

	if (!args[i])
	{
		ft_env(data, args);
		return ;
	}
	while (args[i])
	{
		var = ft_split(args[i], '=');
		if (!var || !var[0])
		{
			free_split(var);
			i++;
			continue ;
		}
		current = data->env;
		prev = NULL;
		while (current != NULL)
		{
			if (strcmp(current->key, var[0]) == 0)
			{
				modify_value(current, var[1]);
				break ;
			}
			prev = current;
			current = current->next;
			if (current == data->env)
			{
				create_var(data, var[0], var[1]);
				break ;
			}
		}
		free_split(var);
		i++;
	}
}
