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
				if (current->type == HEREDOC_TOKEN)
				{
					printf("heredoc filename stored\n");
					node->filenames[i] = get_tmp_file();
					printf("heredoc filename is%s\n", node->filenames[i]);
				}
			}
			node->redir = 1; 
			current->next->processed = 1;
		}
		current = current->next;
	}
}
