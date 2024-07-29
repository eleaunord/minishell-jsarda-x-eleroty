#include "../../../includes/minishell.h"

void	count_redir_out(t_token **tokens, t_node *node)
{
	t_token	*current;
	int		i;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	i = 0;
	while (current)
	{
		if (current->type == REDIR_OUT_TOKEN || current->type == APPEND_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				i++;
			}
		}
		if (current->type == REDIR_OUT_TOKEN)
			node->is_redir_out = 1;
		else if (current->type == APPEND_TOKEN)
			node->is_append = 1;
		current = current->next;
	}
	node->file_out_count = i;
}

void	allocate_memory_for_filename_out(t_node *node)
{
	int i;

	i = 0;
	node->filename_out = (char **)calloc(node->file_out_count + 1,
			sizeof(char *));
	while(i < node->file_out_count)
	{
		node->filename_out[i] =  malloc(sizeof(char) * (sizeof(char) + 1));
		i++;
	}
	node->filename_out[i] = NULL;
	if (!node->filename_out)
	{
		perror("calloc failed");
		exit(EXIT_FAILURE);
	}
}

void	process_filename_out(t_token *tokens, t_node *node)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current)
	{
		if ((current->type == REDIR_OUT_TOKEN || current->type == APPEND_TOKEN )&& current->next
			&& current->next->type == TOKEN_WORD)
		{
			if (i < node->file_out_count)
			{
				node->filename_out[i++] = current->next->value;
			}
			current->next->processed = 1;
		}
		current = current->next;
	}
}
