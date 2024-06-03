
#include "../../../includes/minishell.h"

int word_token(char *input, t_token **tokens, int index)
{
    char    *word;
    int     in_quotes;
    char    quote_char;
    int     word_start;
    int     word_end;

    in_quotes = 0;
    quote_char = '\0';
    word_start = index;

    while (input[index] != '\0')
    {
        if (!in_quotes && (input[index] == ' ' || input[index] == '>' || input[index] == '<'))
        {
            break;
        }
        if (!in_quotes && (input[index] == '"' || input[index] == '\''))
        {
            in_quotes = 1;
            quote_char = input[index];
            index++;
            continue;
        }
        if (in_quotes && input[index] == quote_char)
        {
            in_quotes = 0;
            quote_char = '\0';
            index++;
            continue;
        }
        index++;
    }

    // Only create a token if we have a non-empty word
    if (index > word_start)
    {
        // Adjust start and end positions to remove quotes if present
        word_end = index;
        if (input[word_start] == '"' || input[word_start] == '\'')
        {
            word_start++;
        }
        if (input[word_end - 1] == '"' || input[word_end - 1] == '\'')
        {
            word_end--;
        }
        word = ft_strndup(input + word_start, word_end - word_start);
        if (word)
        {
            add_token_to_list(tokens, new_token(TOKEN_WORD, word));
            free(word);
        }
    }

    // Skip any trailing spaces after the current word token
    while (input[index] == ' ')
    {
        index++;
    }

    return index;
}

int	special_tokens(char *input, t_token **tokens, int index)
{
	if (input[0] == '>')
	{
		if (input[1] == '>')
		{
			add_token_to_list(tokens, new_token(APPEND_TOKEN, ">>"));
			return (index + 2);
		}
		else
		{
			add_token_to_list(tokens, new_token(REDIR_OUT_TOKEN, ">"));
			return (index + 1);
		}
	}
	else if (input[0] == '<')
	{
		if (input[1] == '<')
		{
			add_token_to_list(tokens, new_token(HEREDOC_TOKEN, "<<"));
			return (index + 2);
		}
		else
		{
			add_token_to_list(tokens, new_token(REDIR_IN_TOKEN, "<"));
			return (index + 1);
		}
	}
	return (index + 1);
}

