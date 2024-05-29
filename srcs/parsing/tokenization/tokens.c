#include "../../../includes/minishell.h"
#include <string.h>


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
// t_token	*tokenize_input(char *line)
// {
// 	t_token	*tokens;
	
// 	char	*word;
// 	int		i;
// 	int		start;
// 	int		length;

// 	tokens = NULL;
// 	i = 0;
// 	start = 0;
// 	length = ft_strlen(line);
// 	while (i <= length) // Adjust condition to handle entire string
// 	{
// 		if (line[i] == ' ' || line[i] == '\0')
// 		{
// 			if (i > start) // Ensure non-empty token
// 			{
// 				word = ft_strndup(line + start, i - start);
// 				if (word)
// 				{
// 					add_token_to_list(&tokens, new_token(TOKEN_WORD, word));
// 					free(word);
// 				}
// 			}
// 			start = i + 1; // Update start position for next token
// 		}
// 		i++;
// 	}
// 	return (tokens);
// }


void	word_token(char **input, t_token **tokens)
{
	char	*start;
	char	*word;

	start = *input;
	if (*input > start)
	{
		word = ft_strndup(start, *input - start);
		if (word)
		{
			add_token_to_list(tokens, new_token(TOKEN_WORD, word));
			free(word);
		}
	}
}
void	check_if_inside_quotes(char c, int *in_quotes, char *quote_char)
{
	if (!*in_quotes && (c == '\'' || c == '\"'))
	{
		*in_quotes = 1;
		*quote_char = c;
	}
	else if (*in_quotes && c == *quote_char)
		*in_quotes = 0;
}
t_token	*tokenize_input(char *line)
{
	t_token	*tokens;
	int		start;
	int		length;
	int		i;
	int		inside_quotes;
	char	quote_char;

	inside_quotes = 0;
	quote_char = '\0';
	tokens = NULL;
	i = 0;
	start = 0;
	length = ft_strlen(line);
	while (i <= length)
	{
		// while (line[i] && line[i] == ' ')
		// 	i++;
		// check_if_inside_quotes(line[i], &inside_quotes, &quote_char);
		// if ((line[i] == '>' || line[i] == '<') && !inside_quotes)
		// 	special_tokens(&line, &tokens);
		// else
		word_token(&line, &tokens);
		i++;
	}
	return (tokens);
}