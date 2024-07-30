/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:30:06 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 12:46:06 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*construct_result(char *key_expansion, char *start, char *end,
		char *path_value)
{
	size_t	leading_length;
	size_t	key_length;
	size_t	trailing_length;
	size_t	result_length;
	char	*result;

	leading_length = start - key_expansion;
	key_length = ft_strlen(path_value);
	trailing_length = ft_strlen(end);
	result_length = leading_length + key_length + trailing_length;
	result = (char *)malloc(result_length + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, key_expansion);
	result[leading_length] = '\0';
	ft_strcat(result, path_value);
	ft_strcat(result, end);
	return (result);
}

int	is_in_single_quotes(int in_single_quotes, char c)
{
	if (c == '\'')
		return (!in_single_quotes);
	return (in_single_quotes);
}

int	should_expand_variable(char *token, int index)
{
	return (token[index] == '$' && (token[index + 1] == '{' || !token[index
				+ 1]));
}

int	count_expansions(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->key_expansion != NULL)
		{
			count++;
		}
		current = current->next;
	}
	return (count);
}

void	set_expansions(t_token *tokens, t_node *node)
{
	int	expansion_count;

	if (!tokens || !node)
		return ;
	expansion_count = count_expansions(tokens);
	node->expansion_count = expansion_count;
}
