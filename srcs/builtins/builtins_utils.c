/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:08:36 by juliensarda       #+#    #+#             */
/*   Updated: 2024/06/26 11:42:17 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_swap(t_env *ptr1)
{
	char	*temp_key;
	char	*temp_value;
	int		swapped;

	swapped = 0;
	if (strcmp(ptr1->key, ptr1->next->key) > 0)
	{
		temp_key = ptr1->key;
		temp_value = ptr1->value;
		ptr1->key = ptr1->next->key;
		ptr1->value = ptr1->next->value;
		ptr1->next->key = temp_key;
		ptr1->next->value = temp_value;
		swapped = 1;
		return (swapped);
	}
	return (swapped);
}

void	sort_ascii(t_env *env)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;
	t_env	*start;

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
			swapped = ft_swap(ptr1);
			ptr1 = ptr1->next;
			if (ptr1 == start)
				break ;
		}
		lptr = ptr1;
	}
}

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

void	ft_print_export(t_env *env_dup)
{
	sort_ascii(env_dup);
	print_env(env_dup);
}
