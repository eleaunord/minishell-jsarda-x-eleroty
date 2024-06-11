
#include "../../../includes/minishell.h"

int word_token(char *input, t_token **tokens, int index)
{
    //char    *word;
    int     in_quotes;
    int     word_start;
    int     word_end;

    in_quotes = 0;
    word_start = index;

    while (input[index] != '\0')
    {
        if (!in_quotes && (input[index] == ' ' || input[index] == '>' || input[index] == '<'))
        {
            break;
        }
        close_quote_check(&in_quotes, &in_quotes, NULL, input[index]);
        index++;
    }

    // Only create a token if we have a non-empty word
    if (index > word_start)
    {
        word_end = index;
        // Remove quotes if present
        char *temp_line = ft_strndup(input + word_start, word_end - word_start);
        if (temp_line)
        {
            add_token_to_list(tokens, new_token(TOKEN_WORD, temp_line));
            free(temp_line);
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

