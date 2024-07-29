/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:28:46 by juliensarda       #+#    #+#             */
/*   Updated: 2024/07/29 10:37:29 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_unset(char *value, char *name, char *line)
{
	free(value);
	free(name);
	free(line);
}

void	ft_unset_1(t_env *env, char **args, int i)
{
	t_env	*current;
	t_env	*prev;

	while (args[++i])
	{
		current = env;
		prev = NULL;
		while (current)
		{
			if (ft_strncmp(current->key, args[i],
					ft_strlen(current->key)) == 0)
			{
				if (prev == NULL)
					env = current->next;
				else
					prev->next = current->next;
				free_unset(current->value, current->key, current->str);
				prev = current;
				free(prev);
				break ;
			}
			prev = current;
			current = current->next;
		}
	}
}

void	ft_unset(t_node *data, t_minishell *shell, char **args)
{
	(void)data;
	ft_unset_1(shell->env, args, -1);
	ft_unset_1(shell->env_dup, args, -1);
	g_status = 0;
}
