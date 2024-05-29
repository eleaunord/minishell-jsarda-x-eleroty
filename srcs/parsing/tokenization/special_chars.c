
#include "../../../includes/minishell.h"

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