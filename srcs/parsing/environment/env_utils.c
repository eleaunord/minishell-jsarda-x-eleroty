/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:58:10 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 18:09:22 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_first(t_env **list, t_env *new)
{
	*list = new;
	new->next = NULL;
}

int	append(t_env **list, char *elem)
{
	t_env	*new;
	t_env	*last;

	if (!list_new_elem_str(&new, elem))
		return (0);
	new->next = NULL;
	if (!(*list))
		*list = new;
	else
	{
		last = *list;
		while (last->next != NULL)
		{
			if (last->next == *list)
			{
				perror("Detected circular reference in the list");
				free(new);
				return (0);
			}
			last = last->next;
		}
		last->next = new;
	}
	return (1);
}

char	*recup_shlvl(char *tmp)
{
	char	**split;
	int		lvl;
	char	*char_lvl;

	split = ft_split(tmp, '=');
	if (!split)
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	lvl = ft_atoi(split[1]);
	free(tmp);
	char_lvl = ft_itoa(lvl + 1);
	if (!char_lvl)
	{
		free_tab(split);
		return (NULL);
	}
	tmp = ft_strjoin("SHLVL=", char_lvl);
	free(char_lvl);
	free_tab(split);
	if (!tmp)
		return (NULL);
	return (tmp);
}
