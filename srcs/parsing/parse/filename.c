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

// Fonction pour traiter les tokens et extraire les noms de fichiers
void	process_tokens_for_filenames(t_token *tokens, t_node *node)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				if (current->type == REDIR_IN_TOKEN)
				{
					node->filename_in = current->next->value;
					current->next->processed = 1;
				}
				else if (current->type == REDIR_OUT_TOKEN)
				{
					node->filename_out = current->next->value;
					current->next->processed = 1;
				}
			}
		}
		current = current->next;
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
			if (i == node->limiter_hd_count)
			{
				node->filename_in = get_tmp_file();
			}
			current->next->processed = 1;
		}
		current = current->next;
	}
}

// Fonction principale
void	set_filename(t_token **tokens, t_node *node)
{
	t_token	*tok;

	if (!tokens || !*tokens || !node)
		return ;
	tok = *tokens;
	count_heredocs(&tok, node);
	// Allocation de mémoire pour limiter_hd
	allocate_memory_for_limiter_hd(node);
	// Traitement des tokens pour les noms de fichiers
	process_tokens_for_filenames(*tokens, node);
	// Traitement des tokens HEREDOC_TOKEN
	process_heredoc_tokens(*tokens, node);
	// Null-terminer le tableau limiter_hd
	node->limiter_hd[node->limiter_hd_count] = NULL;
}
