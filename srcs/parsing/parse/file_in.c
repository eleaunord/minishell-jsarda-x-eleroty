#include "../../../includes/minishell.h"

void	count_redir_in(t_token **tokens, t_node *node)
{
	t_token	*current;
	int		i;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	i = 0;
	while (current)
	{
		if (current->type == REDIR_IN_TOKEN)
		{
			node->fdin = -1;
			node->is_redir_in = 1;
			if (current->next && current->next->type == TOKEN_WORD)
			{
				i++;
			}
		}
		current = current->next;
	}
	node->file_in_count = i;
}

void	allocate_memory_for_filename_in(t_node *node)
{
	int	i;

	node->filename_in = (char **)calloc(node->file_in_count + 1,
			sizeof(char *));
	if (!node->filename_in)
	{
		perror("calloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < node->file_in_count)
	{
		node->filename_in[i] = NULL;
		i++;
	}
	node->filename_in[i] = NULL;
}

void	process_filename_in(t_token *tokens, t_node *node)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == REDIR_IN_TOKEN && current->next
			&& current->next->type == TOKEN_WORD)
		{
			if (i < node->file_in_count)
			{
				node->filename_in[i++] = ft_strdup(current->next->value);
			}
			current->next->processed = 1;
		}
		current = current->next;
	}
}
