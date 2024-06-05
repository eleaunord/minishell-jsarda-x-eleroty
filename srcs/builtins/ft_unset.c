/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:22:18 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/05 15:13:24 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_minishell *data, char **args)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 0;
	while (args[i])
	{
		current = data->env;
		prev = NULL;
		while (current != NULL)
		{
			if (strcmp(current->key, args[i]) == 0)
			{
				if (prev == NULL)
					data->env = current->next;
				else
					prev->next = current->next;
				free(current->value);
				free(current->key);
				free(current);
				break; ;
			}
			prev = current;
			current = current->next;
			if (current == data->env)
				break ;
		}
		i++;
	}
}
