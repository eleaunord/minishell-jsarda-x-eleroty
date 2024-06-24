/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:24:48 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/24 17:06:21 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	modify_value(t_env *env, const char *value)
{
	free(env->value);
	env->value = ft_strdup(value);
	if (!env->value)
	{
		perror("strdup");
		return ;
	}
}

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

void	sort_ascii(t_env *env)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;
	t_env	*start;
	char	*temp_key;
	char	*temp_value;

	lptr = NULL;
	start = env;
	if (env == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				temp_key = ptr1->key;
				temp_value = ptr1->value;
				ptr1->key = ptr1->next->key;
				ptr1->value = ptr1->next->value;
				ptr1->next->key = temp_key;
				ptr1->next->value = temp_value;
				swapped = 1;
			}
			ptr1 = ptr1->next;
			if (ptr1 == start)
				break ;
		}
		lptr = ptr1;
	}
}

void	ft_print_export(t_env *env_dup)
{
	if (!env_dup)
		return ; // need to add pwd , shlvl , _
	sort_ascii(env_dup);
	print_env(env_dup);
}

void	ft_export(t_minishell *data, t_node *node, char **args)
{
	int		i;
	t_env	*current;
	t_env	*current_duplicate;
	char	**var;

	(void)node;
	if (!args || !data)
		return ;
	i = 1;
	if (!args[1])
	{
		ft_print_export(data->env_dup);
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
				if (!var[1])
					break ;
				modify_value(current, var[1]);
				break ;
			}
			current = current->next;
			if (current == data->env)
			{
				if (ft_strchr(args[i], '='))
					create_var(current, var[0], var[1]);
				break ;
			}
		}
		current_duplicate = data->env_dup;
		while (current_duplicate)
		{
			if (ft_strcmp(current_duplicate->key, var[0]) == 0)
			{
				if (!var[1])
					break ;
				modify_value(current_duplicate, var[1]);
				break ;
			}
			current_duplicate = current_duplicate->next;
			if (current_duplicate == data->env_dup)
			{
				create_var(current_duplicate, var[0], var[1]);
				break ;
			}
		}
		free_split(var);
		i++;
	}
}
