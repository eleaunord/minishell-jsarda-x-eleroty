/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:21:22 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:40:55 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_args(char *arg, char **name, char **value, char *supp)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*equal = '\0';
		*name = arg;
		if (*(equal + 1) == '\0')
			*value = NULL;
		else
			*value = equal + 1;
		if (!**name)
			return (ft_errors_exec(2, "not a valid identifier", supp, 1), 0);
	}
	else
	{
		*name = arg;
		*value = NULL;
		if (!**name)
			return (ft_errors_exec(2, "not a valid identifier", supp, 1), 0);
	}
	if (!is_valid_identifier(*name))
		return (ft_errors_exec(2, "not a valid identifier", supp, 1), 0);
	return (1);
}

int	modify_value(t_env *env, const char *value)
{
	char	*new_line;
	char	*tmp_name;

	free(env->value);
	env->value = ft_strdup(value);
	if (!env->value)
		return (env->value = NULL, 0);
	tmp_name = ft_strjoin(env->name, "=");
	if (!tmp_name)
		return (free(env->value), env->value = NULL, 0);
	new_line = ft_strjoin(tmp_name, value);
	free(tmp_name);
	if (!new_line)
		return (free(env->value), env->value = NULL, 0);
	free(env->line);
	env->line = new_line;
	return (0);
}

void	handle_env_change(t_shell *shell, char *name, char *value)
{
	t_env	*current;
	char	*tmp_name;
	char	*tmp_line;

	current = shell->envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (!value)
				break ;
			modify_value(current, value);
			break ;
		}
		current = current->next;
	}
	if (value && !current)
	{
		tmp_name = ft_strjoin(name, "=");
		tmp_line = ft_strjoin(tmp_name, value);
		ft_lstadd_back_env(&(shell->envp), ft_lstnew_env(tmp_line, name,
				value));
		free(tmp_name);
		free(tmp_line);
	}
}

void	handle_exp_change(t_shell *shell, char *name, char *value)
{
	t_env	*curr_exp;
	char	*tmp_name;
	char	*tmp_line;

	curr_exp = shell->exp;
	while (curr_exp)
	{
		if (ft_strcmp(curr_exp->name, name) == 0)
		{
			if (!value)
				break ;
			modify_value(curr_exp, value);
			break ;
		}
		curr_exp = curr_exp->next;
	}
	if (!curr_exp)
	{
		tmp_name = ft_strjoin(name, "=");
		if (!value)
			value = "''";
		tmp_line = ft_strjoin(tmp_name, value);
		ft_lstadd_back_env(&(shell->exp), ft_lstnew_env(tmp_line, name, value));
		return (free(tmp_name), free(tmp_line));
	}
}

void	ft_export(t_node *data, t_shell *shell, char **args)
{
	int		i;
	char	*name;
	char	*value;
	char	*supp;

	if (!data)
		return ;
	i = 1;
	if (!args[1])
		return (ft_print_exp(shell->exp, data));
	while (args[i])
	{
		supp = ft_strdup(args[i]);
		if (parse_args(args[i], &name, &value, supp))
		{
			free(supp);
			handle_env_change(shell, name, value);
			handle_exp_change(shell, name, value);
			g_return_satus = 0;
		}
		else
			free(supp);
		supp = NULL;
		i++;
	}
}
