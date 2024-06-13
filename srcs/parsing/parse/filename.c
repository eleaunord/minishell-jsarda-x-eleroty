#include "../../../includes/minishell.h"


// Fonction pour traiter les tokens et extraire les noms de fichiers
// void	process_tokens_for_filenames(t_token *tokens, t_node *node)
// {
// 	t_token	*current;

// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
// 		{
// 			if (current->next && current->next->type == TOKEN_WORD)
// 			{
// 				if (current->type == REDIR_IN_TOKEN)
// 				{
// 					node->filename_in = current->next->value;
// 					current->next->processed = 1;
// 				}
// 				else if (current->type == REDIR_OUT_TOKEN)
// 				{
// 					node->filename_out = current->next->value;
// 					current->next->processed = 1;
// 				}
// 			}
// 		}
// 		current = current->next;
// 	}
// }

// // Fonction pour traiter les tokens HEREDOC_TOKEN
// void	process_heredoc_tokens(t_token *tokens, t_node *node)
// {
// 	int		i;
// 	t_token	*current;

// 	i = 0;
// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == HEREDOC_TOKEN && current->next
// 			&& current->next->type == TOKEN_WORD)
// 		{
// 			if (i < node->limiter_hd_count)
// 			{
// 				node->limiter_hd[i++] = current->next->value;
// 			}
// 			node->here_doc = 1;
// 			if (i == node->limiter_hd_count)
// 			{
// 				node->filename_in = get_tmp_file();
// 			}
// 			current->next->processed = 1;
// 		}
// 		current = current->next;
// 	}
// }

// void	process_filename_in(t_token *tokens, t_node *node)
// {
// 	int		i;
// 	t_token	*current;

// 	i = 0;
// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == REDIR_IN_TOKEN && current->next
// 			&& current->next->type == TOKEN_WORD)
// 		{
// 			if (i < node->file_in_count)
// 			{
// 				node->filename_in[i++] = current->next->value;
// 			}
// 			node->here_doc = 1;
// 			if (i == node->file_in_count)
// 			{
// 				node->filename_in = get_tmp_file();
// 			}
// 			current->next->processed = 1;
// 		}
// 		current = current->next;
// 	}
// }

// void	process_filename_out(t_token *tokens, t_node *node)
// {
// 	int		i;
// 	t_token	*current;

// 	i = 0;
// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == REDIR_OUT_TOKEN && current->next
// 			&& current->next->type == TOKEN_WORD)
// 		{
// 			if (i < node->file_out_count)
// 			{
// 				node->filename_out[i++] = current->next->value;
// 			}
// 			node->here_doc = 1;
// 			if (i == node->file_out_count)
// 			{
// 				node->filename_out = get_tmp_file();
// 			}
// 			current->next->processed = 1;
// 		}
// 		current = current->next;
// 	}
// }

// // Fonction principale filename
// void	set_filename(t_token **tokens, t_node *node)
// {
// 	t_token	*tok;

// 	if (!tokens || !*tokens || !node)
// 		return ;
// 	tok = *tokens;
// 	count_heredocs(&tok, node);
// 	// Allocation de mémoire pour limiter_hd
// 	allocate_memory_for_limiter_hd(node);
// 	// other redirections : in and out
// 	count_redir_in(&tok, node);
// 	allocate_memory_for_filename_in(node);
// 	count_redir_out(&tok, node);
// 	allocate_memory_for_filename_out(node);
// 	// Traitement des tokens pour les noms de fichiers
// 	// process_tokens_for_filenames(*tokens, node);
// 	// Traitement des tokens HEREDOC_TOKEN
// 	process_heredoc_tokens(*tokens, node);
// 	node->limiter_hd[node->limiter_hd_count] = NULL;
// 	// Traitement des tokens REDIR_IN
// 	process_filename_in(*tokens, node);
// 	node->filename_in[node->file_in_count] = NULL;
// 	// Traitement des tokens REDIR_OUT
// 	process_filename_out(*tokens, node);
// 	node->filename_out[node->file_out_count] = NULL;
// }
