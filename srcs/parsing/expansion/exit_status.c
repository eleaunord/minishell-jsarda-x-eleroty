/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:25:57 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 16:23:48 by eleroty          ###   ########.fr       */
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

static char	*allocate_and_copy(char *find, char *status_str, char *pos)
{
	char	*expanded_value;
	size_t	prefix_len;

	prefix_len = pos - find;
	expanded_value = malloc(ft_strlen(find) + ft_strlen(status_str) + 1);
	if (!expanded_value)
		return (NULL);
	ft_strncpy(expanded_value, find, prefix_len);
	ft_strcpy(expanded_value + prefix_len, status_str);
	ft_strcpy(expanded_value + prefix_len + ft_strlen(status_str), pos + 1);
	return (expanded_value);
}

// Function to handle the special case with '?'
char	*handle_special_case(char *find, int status)
{
	char	*status_str;
	char	*expanded_value;
	char	*pos;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	pos = ft_strstr(find, "?");
	if (!pos)
	{
		free(status_str);
		return (NULL);
	}
	expanded_value = allocate_and_copy(find, status_str, pos);
	free(status_str);
	return (expanded_value);
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
