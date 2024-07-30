/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:01:01 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 16:42:10 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
{
	char	*expanded_value;

	if (!node->args || *i >= node->arg_count)
		return ;
	if (ft_strstr(tok->value, "$?") != NULL)
	{
		expanded_value = expand_exit_status(tok->value);
		if (!expanded_value)
			return ;
		node->args[*i] = expanded_value;
		if (node->cmd && ft_strcmp(node->cmd, "$?") == 0)
		{
			free(node->cmd);
			node->cmd = ft_strdup(expanded_value);
		}		
	}
	else if (tok->key_expansion != NULL)
		node->args[*i] = get_expansion(mini, tok->key_expansion);
	else
		node->args[*i] = ft_strdup(tok->value);
	if (!node->args[*i])
	{
		clear_process(node, i);
	}
	(*i)++;
}

void	fill_args(t_token *tokens, t_node *node, t_minishell *mini)
{
	t_token	*tok;
	int		i;

	tok = tokens;
	if (!tokens || !node)
		return ;
	if (node->lonely_expansion == 1)
	{
		node->args[0] = get_expansion(mini, tok->key_expansion);
		node->cmd = get_expansion(mini, tok->key_expansion);
		node->args[1] = NULL;
		return ;
	}
	i = 0;
	while (tok)
	{
		if (tok->type == TOKEN_WORD && !tok->processed)
		{
			process_tok(tok, node, mini, &i);
			if (!node->args)
				return ;
		}
		tok = tok->next;
	}
	node->args[i] = NULL;
}

void	set_filename(t_token **tokens, t_node *node)
{
	t_token	*tok;

	if (!tokens || !*tokens || !node)
		return ;
	tok = *tokens;
	count_heredocs(&tok, node);
	allocate_memory_for_limiter_hd(node);
	count_redir_in(&tok, node);
	allocate_memory_for_filename_in(node);
	count_redir_out(&tok, node);
	allocate_memory_for_filename_out(node);
	process_heredoc_tokens(*tokens, node);
	node->limiter_hd[node->limiter_hd_count] = NULL;
	process_filename_in(*tokens, node);
	process_filename_out(*tokens, node);
	node->filename_out[node->file_out_count] = NULL;
}

void	parse_tokens(t_token *tokens, t_node *node, t_minishell *mini)
{
	if (!tokens)
	{
		return ;
	}
	init_parsing(node);
	set_filename(&tokens, node);
	init_args(tokens, node);
	set_cmd(tokens, node);
	process_expansions(&tokens);
	update_tokens(&tokens, node);
	check_lonely_expansions(tokens, node);
	set_expansions(tokens, node);
	fill_args(tokens, node, mini);
}
