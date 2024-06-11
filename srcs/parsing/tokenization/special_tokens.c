#include "../../../includes/minishell.h"

// Function to handle output redirection tokens
static int	handle_output_redirection(char *input, t_token **tokens, int index)
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

// Function to handle input redirection tokens
static int	handle_input_redirection(char *input, t_token **tokens, int index)
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

// Main function to handle special tokens
int	special_tokens(char *input, t_token **tokens, int index)
{
	if (input[0] == '>')
	{
		return (handle_output_redirection(input, tokens, index));
	}
	else if (input[0] == '<')
	{
		return (handle_input_redirection(input, tokens, index));
	}
	return (index + 1);
}
