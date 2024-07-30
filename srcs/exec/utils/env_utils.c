/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:07:49 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/30 18:08:58 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_swap(t_env *env_dup)
{
	char	*temp_key;
	char	*temp_value;
	int		swapped;

	swapped = 0;
	if (env_dup == NULL || env_dup->next == NULL)
		return (swapped);
	if (ft_strcmp(env_dup->key, env_dup->next->key) > 0)
	{
		temp_key = env_dup->key;
		temp_value = env_dup->value;
		env_dup->key = env_dup->next->key;
		env_dup->value = env_dup->next->value;
		env_dup->next->key = temp_key;
		env_dup->next->value = temp_value;
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
	free_tab(env_tab);
}

void	print_env(t_env *env, t_node *data)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->key)
		{
			write(data->fdout, env->key, ft_strlen(env->key));
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

void	ft_print_exp(t_env *env_dup, t_node *data)
{
	if (env_dup == NULL)
		return ;
	sort_ascii(env_dup, data);
}
