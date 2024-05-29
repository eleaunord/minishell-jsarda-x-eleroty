
#include "../../../includes/minishell.h"

void	word_token(char **input, t_token **tokens, int *start, int *i)
{
	char	*word;

	// If the current position is a space or null terminator, it's a boundary
	if ((*input)[*i] == ' ' || (*input)[*i] == '\0')
	{
		// Only create a token if we have a non-empty word
		if (*i > *start)
		{
			word = ft_strndup(*input + *start, *i - *start);
			if (word)
			{
				add_token_to_list(tokens, new_token(WORD_TOKEN, word));
				free(word);
			}
		}
		// Update the start position to the next character
		*start = *i + 1;
	}
}
void	special_tokens(char **input, t_token **tokens)
{
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			add_token_to_list(tokens, new_token(APPEND_TOKEN, ">>"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(REDIR_OUT_TOKEN, ">"));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			add_token_to_list(tokens, new_token(HEREDOC_TOKEN, "<<"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(REDIR_IN_TOKEN, "<"));
	}
	(*input)++;
}