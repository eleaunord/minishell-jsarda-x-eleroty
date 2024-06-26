/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:24:48 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/26 13:35:11 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_var(t_minishell *data, t_env *env, const char *key,
		const char *value)
{
	t_env	*new_var;

	new_var = allocate_new_var(data);
	if (!new_var)
		return ;
	if (!set_key(new_var, key, data))
		return ;
	if (!set_str(new_var, key, value, data))
		return ;
	if (!set_value(new_var, value, data))
		return ;
	if (env == NULL)
	{
		new_var->next = new_var;
		env = new_var;
	}
	else
		insert_new_var(env, new_var);
}

void	handle_env_change(t_minishell *data, t_env *env, char **var, char *args)
{
	t_env	*current;

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
				create_var(data, current, var[0], var[1]);
			break ;
		}
	}
}

void	handle_env_dup_change(t_minishell *data, t_env *env_dup, char **var)
{
	t_env	*current_duplicate;

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
			create_var(data, current_duplicate, var[0], var[1]);
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
		handle_env_change(data, data->env, var, args[i]);
		handle_env_dup_change(data, data->env_dup, var);
		free_split(var);
		i++;
	}
}
