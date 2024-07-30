/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:25:57 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 14:38:31 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_status(char *str, unsigned long long error_num)
{
	char	*pos;
	size_t	lead_l;
	size_t	trail_l;
	char	*error_num_str;
	char	*expnd;

	pos = ft_strstr(str, "$?");
	if (!pos)
		return (ft_strdup(str));
	lead_l = pos - str;
	trail_l = ft_strlen(pos + 2);
	error_num_str = ft_itoa(error_num);
	if (!error_num_str)
		return (NULL);
	expnd = (char *)malloc(lead_l + ft_strlen(error_num_str) + trail_l + 1);
	if (!expnd)
	{
		free(error_num_str);
		return (NULL);
	}
	ft_memcpy(expnd, str, lead_l);
	ft_memcpy(expnd + lead_l, error_num_str, ft_strlen(error_num_str));
	ft_memcpy(expnd + lead_l + ft_strlen(error_num_str), pos + 2, trail_l + 1);
	free(error_num_str);
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
