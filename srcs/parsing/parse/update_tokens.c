#include "../../../includes/minishell.h"

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
		&& token->key_expansion[strlen(token->key_expansion) - 1] == '"')
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

void	handle_quotes_removal(t_token *token)
{
	char	*new_value;

	if (ft_strchr(token->value, '\'') != NULL || ft_strchr(token->value,
			'"') != NULL)
	{
		new_value = remove_quotes_from_word(token->value);
		free(token->value);
		token->value = new_value;
	}
}

void	handle_dollar_sign_removal(t_token *token)
{
	char	*dollar_sign_pos;
	char	*new_value;

	dollar_sign_pos = ft_strchr(token->value, '$');
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
		handle_quotes_removal(current);
		handle_key_expansion_trimming(current);
		current = current->next;
	}
	// Update the tokens in the linked list of nodes
	while (node)
	{
		node->tokens_in_node = *tokens;
		node = node->next;
	}
}

// void	update_tokens(t_token **tokens, t_node *node)
// {
// 	t_token	*current;
// 	char	*dollar_sign_pos;
// 	char	*new_value;

// 	if (!tokens || !*tokens || !node)
// 		return ;
// 	current = *tokens;
// 	while (current)
// 	{
// 		// Check if the dollar sign is directly followed by a quote
// 		dollar_sign_pos = ft_strchr(current->value, '$');
// 		if (dollar_sign_pos != NULL && (*(dollar_sign_pos + 1) == '\''
// 				|| *(dollar_sign_pos + 1) == '"'))
// 			current->value = remove_dollar_sign(current->value);
// 		if (ft_strchr(current->value, '\'') != NULL || ft_strchr(current->value,
// 				'"') != NULL)
// 		{
// 			new_value = remove_quotes_from_word(current->value);
// 			free(current->value);
// 			current->value = new_value;
// 		}
// 		// New condition: Check if key_expansion is not NULL and is surrounded by double quotes
// 		if (current->key_expansion != NULL &&
// 			current->key_expansion[0] == '"' &&
// 			current->key_expansion[strlen(current->key_expansion) - 1] == '"')
// 		{
// 			// Trim the double quotes from key_expansion
// 			new_value = ft_strtrim(current->key_expansion, "\"");
// 			free(current->key_expansion);
// 			current->key_expansion = new_value;
// 			node->key_expansion = new_value;
// 		}
// 		current = current->next;
// 	}
//         // Update the tokens in the linked list of nodes
//     while (node)
//     {
//         node->tokens_in_node = *tokens;
//         node = node->next;
//     }
// }
