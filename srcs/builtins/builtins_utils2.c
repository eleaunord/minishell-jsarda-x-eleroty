/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:22:19 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 12:32:02 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *line, char *name, char *value)
{
	t_env	*tmp;

	tmp = malloc(sizeof(struct s_env));
	if (!tmp)
		return (0);
	tmp->str = ft_strdup(line);
	tmp->key = ft_strdup(name);
	tmp->value = ft_strdup(value);
	tmp->next = NULL;
	return (tmp);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	tmp = *alst;
	if ((*alst))
	{
		tmp = ft_lstlast_env(*alst);
		tmp->next = new;
	}
	else
	{
		*alst = new;
	}
}
