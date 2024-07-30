/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:01:01 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 13:14:13 by eleroty          ###   ########.fr       */
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

void	process_token(t_token *tok, t_node *node, t_minishell *mini,
		int *arg_index)
{
	char	*expanded_value;

	if (!node->args || *arg_index >= node->arg_count)
		return ;
	if (ft_strstr(tok->value, "$?") != NULL)
	{
		expanded_value = expand_exit_status(tok->value, g_status);
		if (!expanded_value)
			return ;
		node->args[*arg_index] = expanded_value;
		if (node->cmd)
			free(node->cmd);
		node->cmd = ft_strdup(expanded_value);
	}
	else if (tok->key_expansion != NULL)
		node->args[*arg_index] = get_expansion(mini, tok->key_expansion);
	else
		node->args[*arg_index] = ft_strdup(tok->value);
	if (!node->args[*arg_index])
	{
		while (*arg_index > 0)
			free(node->args[--(*arg_index)]);
		free(node->args);
		if (node->cmd)
			free(node->cmd);
		node->args = NULL;
		node->cmd = NULL;
		return ;
	}
	(*arg_index)++;
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
			process_token(tok, node, mini, &i);
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
