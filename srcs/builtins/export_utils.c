/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:11:07 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/26 13:25:39 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	insert_new_var(t_env *env, t_env *new_var)
{
	t_env	*current;

	current = env;
	while (current->next != env)
		current = current->next;
	current->next = new_var;
	new_var->next = env;
}

t_env	*allocate_new_var(t_minishell *data)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		ft_error("malloc : ", strerror(errno), 1, data);
		return (NULL);
	}
	return (new_var);
}

int	set_key(t_env *new_var, const char *key, t_minishell *data)
{
	new_var->key = ft_strdup(key);
	if (!new_var->key)
	{
		ft_error("malloc : ", strerror(errno), 1, data);
		free(new_var);
		return (0);
	}
	return (1);
}

int	set_str(t_env *new_var, const char *key, const char *value,
		t_minishell *data)
{
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
	{
		ft_error("malloc : ", strerror(errno), 1, data);
		return (0);
	}
	if (value)
		new_var->str = ft_strjoin(tmp, value);
	else
		new_var->str = ft_strdup(tmp);
	free(tmp);
	if (!new_var->str)
	{
		ft_error("malloc : ", strerror(errno), 1, data);
		free(new_var->key);
		free(new_var);
		return (0);
	}
	return (1);
}

int	set_value(t_env *new_var, const char *value, t_minishell *data)
{
	if (value)
	{
		new_var->value = ft_strdup(value);
		if (!new_var->value)
		{
			ft_error("malloc : ", strerror(errno), 1, data);
			free(new_var->str);
			free(new_var->key);
			free(new_var);
			return (0);
		}
	}
	else
		new_var->value = NULL;
	return (1);
}
