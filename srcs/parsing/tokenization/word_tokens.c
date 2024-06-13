
#include "../../../includes/minishell.h"

static void	tokenize_word(char *input, t_token **tokens, int index,
		int word_start)
{
	int		word_end;
	char	*temp_line;

	word_end = index;
	temp_line = ft_strndup(input + word_start, word_end - word_start);
	if (temp_line)
	{
		add_token_to_list(tokens, new_token(TOKEN_WORD, temp_line));
		free(temp_line);
	}
}

static int	handle_quotes_and_whitespace(char *input, int index, int *in_quotes)
{
	while (input[index] != '\0')
	{
		if (!(*in_quotes) && (input[index] == ' ' || input[index] == '>'
				|| input[index] == '<'))
		{
			break ;
		}
		close_quote_check(in_quotes, in_quotes, NULL, input[index]);
		index++;
	}
	return (index);
}

int	word_token(char *input, t_token **tokens, int index)
{
	int	in_quotes;
	int	word_start;

	in_quotes = 0;
	word_start = index;
	index = handle_quotes_and_whitespace(input, index, &in_quotes);
	if (index > word_start)
		tokenize_word(input, tokens, index, word_start);
	while (input[index] == ' ')
		index++;
	return (index);
}
// DRAFT

// int	special_tokens(char *input, t_token **tokens, int index)
// {
// 	if (input[0] == '>')
// 	{
// 		if (input[1] == '>')
// 		{
// 			add_token_to_list(tokens, new_token(APPEND_TOKEN, ">>"));
// 			return (index + 2);
// 		}
// 		else
// 		{
// 			add_token_to_list(tokens, new_token(REDIR_OUT_TOKEN, ">"));
// 			return (index + 1);
// 		}
// 	}
// 	else if (input[0] == '<')
// 	{
// 		if (input[1] == '<')
// 		{
// 			add_token_to_list(tokens, new_token(HEREDOC_TOKEN, "<<"));
// 			return (index + 2);
// 		}
// 		else
// 		{
// 			add_token_to_list(tokens, new_token(REDIR_IN_TOKEN, "<"));
// 			return (index + 1);
// 		}
// 	}
// 	return (index + 1);
// }

// int	word_token(char *input, t_token **tokens, int index)
// {
// 	int		in_quotes;
// 	int		word_start;
// 	int		word_end;
// 	char	*temp_line;

// 	in_quotes = 0;
// 	word_start = index;
// 	while (input[index] != '\0')
// 	{
// 		if (!in_quotes && (input[index] == ' ' || input[index] == '>'
// 				|| input[index] == '<'))
// 		{
// 			break ;
// 		}
// 		close_quote_check(&in_quotes, &in_quotes, NULL, input[index]);
// 		index++;
// 	}
// 	if (index > word_start)
// 	{
// 		word_end = index;
// 		temp_line = ft_strndup(input + word_start, word_end - word_start);
// 		if (temp_line)
// 		{
// 			add_token_to_list(tokens, new_token(TOKEN_WORD, temp_line));
// 			free(temp_line);
// 		}
// 	}
// 	while (input[index] == ' ')
// 		index++;
// 	return (index);
// }