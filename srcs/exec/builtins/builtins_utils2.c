/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:22:19 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/30 18:01:51 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *line, char *name, char *value)
{
	t_env	*temp;

	temp = malloc(sizeof(struct s_env));
	if (!temp)
		return (0);
	temp->str = ft_strdup(line);
	temp->key = ft_strdup(name);
	temp->value = ft_strdup(value);
	temp->next = NULL;
	return (temp);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*temp;

	temp = *alst;
	if ((*alst))
	{
		temp = ft_lstlast_env(*alst);
		temp->next = new;
	}
	else
	{
		*alst = new;
	}
}
