/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:23:33 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 13:31:10 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes(char current, bool *in_single_quote,
		bool *in_double_quote)
{
	if (current == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote;
	else if (current == '"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote;
}

static void	handle_delimiter(char **current, char **start, t_node **tokens_list,
		bool *error)
{
	**current = '\0';
	process_segment(*start, tokens_list);
	*start = *current + 1;
	while (**start != '\0' && isspace(**start))
		(*start)++;
	if (**start == '\0')
	{
		*error = true;
		return ;
	}
	*current = *start - 1;
}

static void	process_line(char *line, t_node **tokens_list, bool *error)
{
	char	*start;
	char	*current;
	bool	in_single_quote;
	bool	in_double_quote;

	start = line;
	current = line;
	in_single_quote = false;
	in_double_quote = false;
	*error = false;
	while (*current != '\0')
	{
		handle_quotes(*current, &in_single_quote, &in_double_quote);
		if (*current == '|' && !in_single_quote && !in_double_quote)
		{
			handle_delimiter(&current, &start, tokens_list, error);
			if (*error)
				return ;
		}
		current++;
	}
	process_segment(start, tokens_list);
}

void	split_line(char *line, t_node **tokens_list, bool *error)
{
	if (!line || !tokens_list || !error)
		return ;
	process_line(line, tokens_list, error);
}

bool	ft_split_pipes_spaces(char *line, t_node **tokens_list)
{
	bool	error;

	*tokens_list = NULL;
	split_line(line, tokens_list, &error);
	return (error);
}
