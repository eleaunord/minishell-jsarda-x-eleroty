/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliensarda <juliensarda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:24:48 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/25 12:27:02 by juliensarda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_var(t_env *env, const char *key, const char *value)
{
	t_env	*new_var;
	t_env	*current;

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
	char *tmp = NULL;
	tmp = ft_strjoin(key, "=");
	if (value)
		new_var->str = ft_strjoin(tmp, value);
	else
		new_var->str = ft_strdup(tmp);
	free(tmp);
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
	}
	else
		new_var->value = NULL;
	if (env == NULL)
		new_var->next = new_var;
	else
	{
		current = env;
		while (current->next != env)
			current = current->next;
		current->next = new_var;
		new_var->next = env;
	}
	env = new_var;
}

void	ft_print_export(t_env *env_dup)
{
	if (!env_dup)
		return ; // need to add pwd , shlvl , _ parsing
	sort_ascii(env_dup);
	print_env(env_dup);
}

void	handle_env_change(t_env *env, char **var, char *args)
{
	t_env *current;

	current = env;
	while (current)
		{
			if (ft_strcmp(current->key, var[0]) == 0)
			{
				if (count_args(var) <= 1)
					break ;
				modify_value(current, var[1]);
				break ;
			}
			current = current->next;
			if (current == env)
			{
				if (ft_strchr(args, '='))
					create_var(current, var[0], var[1]);
				break ;
			}
		}
}

void	handle_env_dup_change(t_env *env_dup, char **var)
{
	t_env *current_duplicate;
	current_duplicate = env_dup;
		while (current_duplicate)
		{
			if (ft_strcmp(current_duplicate->key, var[0]) == 0)
			{
				if (count_args(var) <= 1)
					break ;
				modify_value(current_duplicate, var[1]);
				break ;
			}
			current_duplicate = current_duplicate->next;
			if (current_duplicate == env_dup)
			{
				create_var(current_duplicate, var[0], var[1]);
				break ;
			}
		}
}

void	ft_export(t_minishell *data, t_node *node, char **args)
{
	int		i;
	char	**var;

	(void)node;
	if (!args || !data)
		return ;
	i = 1;
	if (!args[1])
		return (ft_print_export(data->env_dup));
	while (args[i])
	{
		var = ft_split(args[i], '=');
		if (!var || !var[0])
		{
			free_split(var);
			var[1] = NULL;
			var = NULL;
			i++;
			continue ;
		}
		handle_env_change(data->env, var, args[i]);
		handle_env_dup_change(data->env_dup, var);
		free_split(var);
		i++;
	}
}
