/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:22:18 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/24 13:24:33 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset_env(t_env *data, char **args)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 0;
	while (args[i])
	{
		current = data;
		prev = NULL;
		while (current != NULL)
		{
			if (ft_strcmp(current->key, args[i]) == 0)
			{
				if (prev == NULL)
					data = current->next;
				else
					prev->next = current->next;
				free(current->value);
				free(current->key);
				prev = current;
				break ;
			}
			prev = current;
			current = current->next;
			if (current == data)
				break ;
		}
		i++;
	}
}

void	ft_unset(t_minishell *data, t_node *node, char **args)
{
	(void)node;
	ft_unset_env(data->env, args);
	ft_unset_env(data->env_dup, args);
}
