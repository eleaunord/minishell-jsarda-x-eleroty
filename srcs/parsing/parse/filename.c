#include "../../../includes/minishell.h"

void	count_redirections(t_token **tokens, t_node *node)
{
	t_token	*current;
	int		i;
	int		j;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	i = 0;
	j = 0;
	while (current)
	{
		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
		{
			if (current->type == HEREDOC_TOKEN && current->next
				&& current->next->type == TOKEN_WORD)
				j++;
			if (current->next && current->next->type == TOKEN_WORD)
				i++;
		}
		current = current->next;
	}
	node->file_count = i;
	node->limiter_hd_count = j;
}

void	allocate_memory_for_filenames(t_node *node)
{
	node->filenames = (char **)calloc(node->file_count + 1, sizeof(char *));
	if (!node->filenames)
	{
		perror("calloc failed");
		exit(EXIT_FAILURE);
	}
}
void	allocate_memory_for_limiter_hd(t_node *node)
{
	node->limiter_hd = (char **)calloc(node->limiter_hd_count + 1,
			sizeof(char *));
	if (!node->limiter_hd)
	{
		perror("calloc failed");
		exit(EXIT_FAILURE);
	}
}

void	process_filenames(t_token *tokens, t_node *node)
{
	int		i;
	int		j;
	t_token	*current;

	i = 0;
	j = 0;
	current = tokens;
    while (current)
    {
        if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN && current->next
            && current->next->type == TOKEN_WORD)
        {
            if (i < node->file_count)
            {
                if (current->type == HEREDOC_TOKEN && j < node->limiter_hd_count)
                {
                    node->limiter_hd[j++] = current->next->value;
					node->last_heredoc = current->next->value;
				}
                else
                    node->filenames[i++] = current->next->value;
            }
            node->redir = 1;
            current->next->processed = 1;
        }
        current = current->next;
    }
}
