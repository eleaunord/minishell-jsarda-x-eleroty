#include "../../../includes/minishell.h"
#include <string.h>

// t_token	*new_token(t_token_type type, char *value)
// {
// 	t_token	*token;

// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// 	token->type = type;
// 	token->value = ft_strdup(value);
// 	if (!token->value)
// 	{
// 		free(token);
// 		return (NULL);
// 	}
// 	token->next = NULL;
// 	return (token);
// }
// void	add_token_to_list(t_token **tokens, t_token *new_token)
// {
// 	t_token	*last;

// 	if (!*tokens)
// 		*tokens = new_token;
// 	else
// 	{
// 		last = *tokens;
// 		while (last->next)
// 			last = last->next;
// 		last->next = new_token;
// 	}
// }

// void	add_word_token_if_valid(char **start, char **input, t_token **tokens)
// {
// 	char	*word;

// 	if (*input > *start)
// 	{
// 		word = ft_strndup(*start, *input - *start);
// 		if (word)
// 		{
// 			add_token_to_list(tokens, new_token(TOKEN_WORD, word));
// 			free(word);
// 		}
// 	}
// }
// void	handle_word(char **input, t_token **tokens)
// {
// 	char	*start;

// 	start = *input;
// 	add_word_token_if_valid(&start, input, tokens);
// }
// t_token	*tokenize_input(char *input)
// {
// 	t_token	*tokens;

// 	tokens = NULL;
// 	while (*input)
// 	{
//         handle_word(&input, &tokens);
// 	}
//     t_token *current;
//     current = tokens;
// 	while (current != NULL)
// 	{
// 		printf("Token value : %s\n", (char *)current->value);
// 		printf("Token type : %s\n", (char *)current->value);
// 		current = current->next;
// 	}
// 	return (tokens);
// }

// Function to create a new token
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

// Function to tokenize input
t_token	*tokenize_input(char *line)
{
	t_token	*tokens;
	
	char	*word;
	int		i;
	int		start;
	int		length;

	tokens = NULL;
	i = 0;
	start = 0;
	length = ft_strlen(line);
	while (i <= length) // Adjust condition to handle entire string
	{
		if (line[i] == ' ' || line[i] == '\0')
		{
			if (i > start) // Ensure non-empty token
			{
				word = ft_strndup(line + start, i - start);
				if (word)
				{
					add_token_to_list(&tokens, new_token(TOKEN_WORD, word));
					free(word);
				}
			}
			start = i + 1; // Update start position for next token
		}
		i++;
	}
	return (tokens);
}
