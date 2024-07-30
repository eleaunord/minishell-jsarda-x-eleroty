/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:13:42 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 14:15:48 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_params(t_token *tokens, t_node *node)
{
	if (!tokens || !node)
		return (0);
	if (!node->args)
		return (0);
	return (1);
}

static void	set_null(t_node *node)
{
	if (node)
	{
		node->cmd = NULL;
		node->args[0] = NULL;
	}
}

static void	clear_cmd(t_node *node)
{
	if (node && node->cmd)
	{
		free(node->cmd);
		node->cmd = NULL;
	}
}

void	set_cmd(t_token *tokens, t_node *node)
{
	t_token	*tok;

	if (!check_params(tokens, node))
		return ;
	tok = tokens;
	while (tok != NULL)
	{
		if (tok->type == TOKEN_WORD)
		{
			if (!tok->processed)
			{
				clear_cmd(node);
				node->cmd = ft_strdup(tok->value);
				node->args[0] = node->cmd;
				node->args[1] = NULL;
				if (!node->cmd)
					return ;
				return ;
			}
		}
		else if (tok->type >= APPEND_TOKEN && tok->type <= REDIR_IN_TOKEN)
			tok->processed = 1;
		tok = tok->next;
	}
	set_null(node);
}
