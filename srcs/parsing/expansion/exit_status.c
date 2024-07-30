/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:25:57 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 15:56:43 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_status(char *str)
{
	char	*pos;
	size_t	lead_l;
	size_t	trail_l;
	char	*error_str;
	char	*expnd;

	pos = ft_strstr(str, "$?");
	if (!pos)
		return (ft_strdup(str));
	lead_l = pos - str;
	trail_l = ft_strlen(pos + 2);
	error_str = ft_itoa(g_status);
	if (!error_str)
		return (NULL);
	expnd = (char *)malloc(lead_l + ft_strlen(error_str) + trail_l + 1);
	if (!expnd)
	{
		free(error_str);
		return (NULL);
	}
	ft_memcpy(expnd, str, lead_l);
	ft_memcpy(expnd + lead_l, error_str, ft_strlen(error_str));
	ft_memcpy(expnd + lead_l + ft_strlen(error_str), pos + 2, trail_l + 1);
	free(error_str);
	return (expnd);
}

void	clear_process(t_node *node, int *i)
{
	if (node)
	{
		while (*i > 0)
			free(node->args[--(*i)]);
		free(node->args);
		node->args = NULL;
		if (node->cmd)
		{
			free(node->cmd);
			node->cmd = NULL;
		}
	}
}
