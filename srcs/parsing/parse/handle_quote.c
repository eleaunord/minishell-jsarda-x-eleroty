/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:45:14 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 16:07:21 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_unquoted_token(t_token *tok, t_minishell *mini, t_node *node,
		int *i)
{
	char	*expanded_value;

	expanded_value = get_expansion(ft_strdup(tok->value), &mini->env);
	if (!expanded_value)
	{
		clear_process(node, i);
		return ;
	}
	if (node->args[*i])
	{
		free(node->args[*i]);
		node->args[*i] = NULL;
	}
	node->args[*i] = strip_quotes(0, 0, expanded_value, 0);
	if (!node->args[*i])
	{
		clear_process(node, i);
		return ;
	}
	if (*i == 0)
		node->cmd = ft_strdup(node->args[*i]);
	(*i)++;
}

static void	handle_squoted_token(t_token *tok, t_node *node, int *i)
{
	if (node->args[*i])
	{
		free(node->args[*i]);
		node->args[*i] = NULL;
	}
	node->args[*i] = strip_quotes(0, 0, ft_strdup(tok->value), 0);
	if (!node->args[*i])
	{
		clear_process(node, i);
		return ;
	}
	if (*i == 0)
		node->cmd = ft_strdup(node->args[*i]);
	(*i)++;
}

void	process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
{
	if (!node->args || *i >= node->arg_count)
		return ;
	if (tok->sq == 1)
	{
		handle_squoted_token(tok, node, i);
	}
	else
	{
		handle_unquoted_token(tok, mini, node, i);
	}
}
