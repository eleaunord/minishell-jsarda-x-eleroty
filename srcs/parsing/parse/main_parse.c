/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:00:34 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 13:05:54 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_node(t_node *current, t_minishell *mini)
{
	t_token	*tokens;

	tokens = tokenize_input(current->content);
	if (!tokens)
	{
		freelist(&current);
		mini->nodes = NULL;
		return (0);
	}
	parse_tokens(tokens, current, mini);
	return (1);
}

static int	process_tokens(t_node **nodes, t_minishell *mini)
{
	t_node	*current;

	current = *nodes;
	mini->nodes = *nodes;
	while (current != NULL)
	{
		if (process_node(current, mini) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

static int	handle_error(char *line_copy, t_node **nodes)
{
	write(1, "Syntax error\n", 13);
	free(line_copy);
	freelist(nodes);
	return (0);
}

int	tokenizer(char *line, t_node **nodes, t_minishell *mini)
{
	char	*line_copy;

	if (open_quote_check(line))
		return (0);
	line_copy = ft_strdup(line);
	if (!line_copy)
		return (0);
	if (ft_split_pipes_spaces(line_copy, nodes))
		return (handle_error(line_copy, nodes));
	free(line_copy);
	return (process_tokens(nodes, mini));
}

int	process_input_line(char *input_line, t_node **node_list, t_minishell *data)
{
	if (check_line(&input_line))
	{
		free(input_line);
		return (0);
	}
	if (!tokenizer(input_line, node_list, data))
	{
		add_history(input_line);
		free(input_line);
		return (0);
	}
	return (1);
}
