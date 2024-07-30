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
void	init_args(t_token *tokens, t_node *node)
{
	int	arg_count;

	arg_count = count_arguments(tokens);
	node->args = (char **)ft_calloc(arg_count + 1, sizeof(char *));	
	if (!node->args)
		return ;
	node->arg_count = arg_count;
}

void	set_cmd(t_token *tokens, t_node *node)
{
	t_token	*tok;

	tok = tokens;
	if (!tokens || !node)
		return ;
	if (!node->args)
		return;
	while (tok != NULL)
	{
		if (tok->type == TOKEN_WORD)
		{
			if (!tok->processed)
			{
				if (node->cmd)
				{
					free(node->cmd);
					node->cmd = NULL;
				}
				node->cmd = ft_strdup(tok->value);
				node->args[0] = node->cmd;
				node->args[1] = NULL;
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
	node->cmd = NULL;
	node->path = NULL;
	node->args = NULL;
	node->is_redir_out = 0;
	node->is_redir_in = 0;
	node->fdintmp = 0;
	node->fdout = 1;
	node->fdin = 0;
	node->filename_in = NULL;
	node->filename_out = NULL;
	node->is_here_doc = 0;
	node->limiter_hd = NULL;
	node->last_heredoc = NULL;
	node->limiter_hd_count = 0;
	node->file_in_count = 0;
	node->file_out_count = 0;
	node->error_num = 0;
	node->pid = -42;
	node->arg_count = 0;
	node->key_expansion = NULL;
	node->expansion_count = 0;
	node->lonely_expansion = 0;
}

