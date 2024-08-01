/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:21:49 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 16:25:20 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_dollar_sign(char *str)
{
	char	*new_str;
	char	*ptr;

	new_str = ft_strdup(str);
	ptr = ft_strchr(new_str, '$');
	if (ptr != NULL)
	{
		ft_strcpy(ptr, ptr + 1);
	}
	return (new_str);
}

void	handle_key_expansion_trimming(t_token *token)
{
	char	*new_value;

	new_value = NULL;
	if (token->key_expansion != NULL && token->key_expansion[0] == '"'
		&& token->key_expansion[ft_strlen(token->key_expansion) - 1] == '"')
	{
		new_value = ft_strtrim(token->key_expansion, "\"");
		free(token->key_expansion);
		token->key_expansion = new_value;
	}
	else if (token->key_expansion != NULL && ft_strchr(token->key_expansion,
			'$'))
	{
		new_value = ft_strtrim(token->key_expansion, "$");
		free(token->key_expansion);
		token->key_expansion = new_value;
	}
	if (new_value != NULL && *new_value == '\0')
	{
		free(new_value);
	}
}

void	handle_dollar_sign_removal(t_token *token)
{
	char	*dollar_sign_pos;
	char	*new_value;

	dollar_sign_pos = ft_strchr(token->value, '$');
	if (dollar_sign_pos != NULL && token->key_expansion == NULL)
		return ;
	if (dollar_sign_pos != NULL && (*(dollar_sign_pos + 1) == '\''
			|| *(dollar_sign_pos + 1) == '"'))
	{
		new_value = remove_dollar_sign(token->value);
		free(token->value);
		token->value = new_value;
	}
}

void	update_tokens(t_token **tokens, t_node *node)
{
	t_token	*current;

	if (!tokens || !*tokens || !node)
		return ;
	current = *tokens;
	while (current)
	{
		handle_dollar_sign_removal(current);
		handle_key_expansion_trimming(current);
		current = current->next;
	}
	while (node)
	{
		node->tokens_in_node = *tokens;
		node = node->next;
	}
}
