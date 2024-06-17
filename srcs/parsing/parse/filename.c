#include "../../../includes/minishell.h"

void	count_redirections(t_token **tokens, t_node *node)
{
	t_token	*current;
	int		i;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	i = 0;
	while (current)
	{
		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				i++;
			}
		}
		current = current->next;
	}
	node->file_count = i;
}

void	allocate_memory_for_filenames(t_node *node)
{
	node->filenames = (char **)calloc(node->file_count + 1,
			sizeof(char *));
	if (!node->filenames)
	{
		perror("calloc failed");
		exit(EXIT_FAILURE);
	}
}

void	process_filenames(t_token *tokens, t_node *node)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN && current->next
			&& current->next->type == TOKEN_WORD)
		{
			if (i < node->file_count)
			{
				node->filenames[i++] = current->next->value;
			}
			node->redir = 1; 
			if (i == node->file_count)
			{
				node->filenames[i] = get_tmp_file();
				printf("file name out : %s", node->filenames[i]);
			}
			current->next->processed = 1;
		}
		current = current->next;
	}
}
