#include "../../../includes/minishell.h"

/*
echo "'hey tu vas chew moi' 'non'" =>

	ARG[0]: 'hey
	ARG[1]: tu
	ARG[2]: vas
	ARG[3]: chez
	ARG[4]: moi'
	ARG[5]: 'non'
*/

int	count_arguments(t_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == TOKEN_WORD)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	handle_redirection_token(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next_token;
	int		flags;

	if (!tokens || !*tokens || !(*tokens)->next)
		return ;
	tmp = *tokens;
	next_token = tmp->next;
	if (next_token && next_token->type == TOKEN_WORD)
	{
		// Determine the flags for opening the file
		flags = O_CREAT | O_RDWR;
		if (tmp->type == APPEND_TOKEN)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		// Process the redirection based on type
		tmp->filename = next_token->value;
		tmp->sstdout = open(next_token->value, flags, 0644);
		if (tmp->sstdout < 0)
		{
			perror("open");
			return ;
		}
		// Mark the tokens as processed
		tmp->processed = 1;
		next_token->processed = 1;
		// Move past the redirection token and its argument
		*tokens = next_token->next;
	}
	else
	{
		// If there's no valid next token, move to the next token
		*tokens = tmp->next;
	}
}

void	process_redirection(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
		{
			handle_redirection_token(&current);
		}
		else
		{
			// Move to the next token if it's not a redirection
			current = current->next;
		}
	}
}
void	parse_tokens(t_token *tokens)
{
	int		arg_count;
	int		i;
	t_token	*tmp;
	t_token	*next;

	if (!tokens)
		return ;
	// Set the first token's value to cmd
	tokens->cmd = ft_strdup(tokens->value);
	if (!tokens->cmd)
		return ;
	// Process redirections first
	process_redirection(&tokens);
	// Move to the next token for counting arguments
	tmp = tokens->next;
	arg_count = count_arguments(tmp);
	tokens->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!tokens->args)
	{
		free(tokens->cmd);
		return ;
	}
	i = 0;
	while (tmp && i < arg_count)
	{
		if (tmp->type == TOKEN_WORD && !tmp->processed)
		{
			tokens->args[i] = ft_strdup(tmp->value);
			if (!tokens->args[i])
			{
				// Handle strdup failure, free allocated memory
				while (i > 0)
				{
					free(tokens->args[--i]);
				}
				free(tokens->args);
				free(tokens->cmd);
				return ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	tokens->args[arg_count] = NULL;
	// Free the original list except the first token since we need to preserve tokens->cmd
	tmp = tokens->next;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->processed == 0)
		{
			free(tmp->value);
			free(tmp);
		}
		tmp = next;
	}
	tokens->next = NULL;
}
