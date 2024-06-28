/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliensarda <juliensarda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:22:18 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/27 10:08:17 by juliensarda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_unset_env(t_env **data, char **args, int i)
{
	t_env	*current;
	t_env	*prev;
	t_env	*head;

	while (args[++i])
	{
		current = *data;
		prev = NULL;
		head = *data;

		do
		{
			// Skip the '_' key
			if (ft_strcmp(current->key, "_") == 0)
			{
				prev = current;
				current = current->next;
				continue;
			}

			if (ft_strcmp(current->key, args[i]) == 0)
			{
				if (prev == NULL)
				{
					// Handle the case where the node to be removed is the head
					t_env *tail = head;
					while (tail->next != head)
						tail = tail->next;

					if (current->next == current)
					{
						// The list has only one element
						*data = NULL;
					}
					else
					{
						*data = current->next;
						tail->next = current->next;
					}
				}
				else
				{
					prev->next = current->next;
				}
				
				free(current->key);
				free(current->value);
				free(current);

				break;
			}

			prev = current;
			current = current->next;
		} while (current != head);
	}
}


void	ft_unset(t_minishell *data, t_node *node, char **args)
{
	(void)node;
	ft_unset_env(&data->env, args, -1);
	ft_unset_env(&data->env_dup, args, -1);
}
