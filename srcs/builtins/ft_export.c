/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:24:48 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/19 09:48:39 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	modify_value(t_env *current, const char *value)
{
	free(current->value);
	current->value = ft_strdup(value);
	if (!current->value)
	{
		perror("strdup");
		return ;
	}
	free(current->str);
	current->str = malloc(ft_strlen(current->key) + ft_strlen(current->value)
			+ 2);
	if (!current->str)
	{
		perror("malloc");
		return ;
	}
	sprintf(current->str, "%s=%s", current->key, current->value);
}

void	create_var(t_minishell *data, const char *key, const char *value)
{
	t_env	*new_var;
	t_env	*current;
	size_t	value_size;
	size_t	key_size;

	key_size = 0;
	value_size = 0;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("malloc");
		return ;
	}
	new_var->key = ft_strdup(key);
	if (!new_var->key)
	{
		perror("strdup");
		free(new_var);
		return ;
	}
	if (value)
	{
		new_var->value = ft_strdup(value);
		if (!new_var->value)
		{
			perror("strdup");
			free(new_var->key);
			free(new_var);
			return ;
		}
		value_size = ft_strlen(value);
	}
	else
		new_var->value = NULL;
	key_size = ft_strlen(key);
	new_var->str = malloc(key_size + value_size + 2);
	if (!new_var->str)
	{
		perror("malloc");
		free(new_var->key);
		free(new_var->value);
		free(new_var);
		return ;
	}
	if (data->env == NULL)
		new_var->next = new_var;
	else
	{
		current = data->env;
		while (current->next != data->env)
			current = current->next;
		current->next = new_var;
		new_var->next = data->env;
	}
	data->env = new_var;
}

void	ft_export(t_minishell *data, t_node *node, char **args)
{
	int		i;
	t_env	*current;
	char	**var;

	if (!args || !data)
		return ;
	i = 1;
	if (!args[1])
	{
		ft_env(data, node, args);
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
		while (current)
		{
			if (ft_strcmp(current->key, var[0]) == 0)
			{
				modify_value(current, var[1]);
				break ;
			}
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
