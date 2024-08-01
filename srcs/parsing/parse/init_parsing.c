/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:00:00 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 16:13:56 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD && !current->processed)
		{
			count++;
		}
		current = current->next;
	}
	return (count);
}

void	init_args(t_token *tokens, t_node *node)
{
	int	arg_count;

	arg_count = count_arguments(tokens);
	node->args = (char **)ft_calloc(arg_count + 1, sizeof(char *));
	if (!node->args)
		return ;
	node->arg_count = arg_count;
}

void	init_parsing(t_node *node)
{
	node->cmd = NULL;
	node->path = NULL;
	node->args = NULL;
	node->is_redir_out = 0;
	node->is_redir_in = 0;
	node->fdintmp = 0;
	node->fdout = 1;
	node->fdin = 0;
	node->filename_in = NULL;
	node->filename_out = NULL;
	node->is_here_doc = 0;
	node->limiter_hd = NULL;
	node->last_heredoc = NULL;
	node->limiter_hd_count = 0;
	node->file_in_count = 0;
	node->file_out_count = 0;
	node->error_num = 0;
	node->pid = -42;
	node->arg_count = 0;
	node->key_expansion = NULL;
	node->lonely_expansion = 0;
}
