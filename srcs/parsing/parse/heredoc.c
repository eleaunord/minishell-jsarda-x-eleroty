#include "../../../includes/minishell.h"

void	count_heredocs(t_token **tokens, t_node *node)
{
	t_token	*current;
	int		i;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	i = 0;
	while (current)
	{
		if (current->type == HEREDOC_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				i++;
			}
		}
		current = current->next;
	}
	node->limiter_hd_count = i;
}

// Fonction pour allouer de la mémoire pour limiter_hd
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

// Fonction pour traiter les tokens HEREDOC_TOKEN
void	process_heredoc_tokens(t_token *tokens, t_node *node)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == HEREDOC_TOKEN && current->next
			&& current->next->type == TOKEN_WORD)
		{
			if (i < node->limiter_hd_count)
			{
				node->limiter_hd[i++] = current->next->value;
			}
			node->here_doc = 1;
			// if (i == node->limiter_hd_count)
			// {
			// 	node->filename_in = get_tmp_file();
			// }
			current->next->processed = 1;
		}
		current = current->next;
	}
}

