#include "../../../includes/minishell.h"
#include <string.h>

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->cmd = NULL;
	token->args = NULL;
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

// Function to add a token to the list
void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}
t_token	*tokenize_input(char *node)
{
	t_token	*tokens;
	int		start;
	int		length;
	int		i;

	tokens = NULL;
	i = 0;
	start = 0;
	length = ft_strlen(node);
	while (i <= length)
	{
		if (node[i] == '>' || node[i] == '<')
			special_tokens(&node, &tokens);
		else
			word_token(&node, &tokens, &start, &i);
		i++;
	}
	return (tokens);
}