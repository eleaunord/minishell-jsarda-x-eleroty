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
		if (current->type == REDIR_OUT_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				i++;
			}
		}
		current = current->next;
	}
	node->file_out_count = i;
}

void	allocate_memory_for_filename_out(t_node *node)
{
	node->filename_out = (char **)calloc(node->file_out_count + 1,
			sizeof(char *));
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
		if (current->type == REDIR_OUT_TOKEN && current->next
			&& current->next->type == TOKEN_WORD)
		{
			if (i < node->file_out_count)
			{
				node->filename_out[i++] = current->next->value;
			}
			node->here_doc = 1; 
			if (i == node->file_out_count)
			{
				node->filename_out[i] = get_tmp_file();
				printf("file name out : %s", node->filename_out[i]);
			}
			current->next->processed = 1;
		}
		current = current->next;
	}
}
