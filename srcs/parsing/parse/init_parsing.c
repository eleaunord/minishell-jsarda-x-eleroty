#include "../../../includes/minishell.h"

int	count_arguments(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD && !current->processed)
		{
			count++;
		}
		current = current->next;
	}
	return (count);
}
int	init_args(t_token *tokens, t_node *node)
{
	int	arg_count;

	arg_count = count_arguments(tokens);
	node->args = (char **)ft_calloc(arg_count + 1, sizeof(char *));
	node->arg_count = arg_count;
	if (!node->args)
	{
		free(node->cmd);
		return (-1);
	}
	return (0);
}

void	set_cmd(t_token *tokens, t_node *node)
{
	t_token	*tok;

	tok = tokens;
	if (!tokens || !node)
		return ;
	while (tok != NULL)
	{
		if (tok->type == TOKEN_WORD)
		{
			// Check if it's the first TOKEN_WORD after a redirection
			if (!tok->processed)
			{
				node->cmd = ft_strdup(tok->value);
				node->args[0] = node->cmd;
				if (!node->cmd)
					return ;
				return ;
			}
		}
		else if (tok->type >= APPEND_TOKEN && tok->type <= REDIR_IN_TOKEN)
			tok->processed = 1;
		tok = tok->next;
	}
	node->cmd = NULL;
	node->args[0] = NULL;
}

void	init_parsing(t_node *node)
{
	// From parsing to exec
	node->args = NULL;
	node->arg_count = 0;
	node->cmd = NULL;
	node->filename_out = NULL;
	node->filename_in = NULL;
	node->here_doc = 0;
	node->limiter_hd = NULL;
	node->limiter_hd_count = 0;
	node->key_expansion = NULL;
}