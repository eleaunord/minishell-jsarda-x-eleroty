/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:07:49 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:41:42 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_swap(t_env *exp)
{
	char	*temp_name;
	char	*temp_value;
	int		swapped;

	swapped = 0;
	if (exp == NULL || exp->next == NULL)
		return (swapped);
	if (strcmp(exp->name, exp->next->name) > 0)
	{
		temp_name = exp->name;
		temp_value = exp->value;
		exp->name = exp->next->name;
		exp->value = exp->next->value;
		exp->next->name = temp_name;
		exp->next->value = temp_value;
		swapped = 1;
		return (swapped);
	}
	return (swapped);
}

char	**ft_sort_ascii(char **av)
{
	int		i;
	int		j;
	int		len;
	char	*swap;

	len = ft_tablen(av);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			if (ft_strcmp(av[i], av[j]) < 0)
			{
				swap = av[i];
				av[i] = av[j];
				av[j] = swap;
			}
			j++;
		}
		i++;
	}
	return (av);
}

void	sort_ascii(t_env *env, t_node *data)
{
	char	**env_tab;
	int		i;

	env_tab = create_char_env(env, get_env_list_size(env));
	env_tab = ft_sort_ascii(env_tab);
	i = 0;
	while (env_tab[i])
	{
		write(data->fdout, "export ", 7);
		write(data->fdout, env_tab[i], ft_strlen(env_tab[i]));
		write(data->fdout, "\n", 1);
		i++;
	}
	freetab(env_tab);
}

void	print_env(t_env *env, t_node *data)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->name)
		{
			write(data->fdout, env->name, ft_strlen(env->name));
		}
		if (env->value)
		{
			write(data->fdout, "=", 1);
			write(data->fdout, env->value, ft_strlen(env->value));
		}
		write(data->fdout, "\n", 1);
		env = env->next;
	}
}

void	ft_print_exp(t_env *exp, t_node *data)
{
	if (exp == NULL)
		return ;
	sort_ascii(exp, data);
}
