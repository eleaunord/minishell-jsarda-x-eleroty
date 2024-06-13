#include "../../../includes/minishell.h"
<<<<<<< HEAD
=======
#include <stdbool.h>

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
// A reduire apres merge exec
void	set_filename(t_token **tokens, t_node *node)
{
	t_token	*current;
	t_token	*tok;
	int		i;

	if (!tokens || !*tokens || !node)
		return ;
	tok = *tokens;
	count_heredocs(&tok, node);
	i = 0;
	node->limiter_hd = (char **)calloc(node->limiter_hd_count + 1,
			sizeof(char *));
	if (!node->limiter_hd)
	{
		return ;
	}
	current = *tokens;
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
				else if (current->type == HEREDOC_TOKEN)
				{
					if (i < node->limiter_hd_count) {
                        node->limiter_hd[i] = current->next->value;
                        i++;
                    }
                    node->here_doc = 1;
					printf("node->limiter_hd_count : %d\n", node->limiter_hd_count);
					printf("i : %d\n", i);
                    if (i == node->limiter_hd_count)
					{
						printf("creating file\n");
                        node->filename_in = get_tmp_file();
                    }
                    current->next->processed = 1;
				}
			}
		}
		current = current->next;
	}
	node->limiter_hd[node->limiter_hd_count] = NULL;
}
>>>>>>> origin/exec

void	fill_args(t_token *tokens, t_node *node)
{
	t_token	*tok;
	int		i;

	tok = tokens;
	if (!tokens || !node)
		return ;
	i = -1;
	while (tok)
	{
		if (tok->type == TOKEN_WORD && !tok->processed)
		{
			node->args[++i] = ft_strdup(tok->value);
			if (!node->args[i])
			{
				while (i > 0)
				{
					free(node->args[--i]);
				}
				free(node->args);
				free(node->cmd);
				return ;
			}
		}
		tok = tok->next;
	}
}

// Fonction principale filename
void	set_filename(t_token **tokens, t_node *node)
{
	t_token	*tok;

	if (!tokens || !*tokens || !node)
		return ;
	tok = *tokens;
	count_heredocs(&tok, node);
	// Allocation de mémoire pour limiter_hd
	allocate_memory_for_limiter_hd(node);
	// other redirections : in and out
	count_redir_in(&tok, node);
	allocate_memory_for_filename_in(node);
	count_redir_out(&tok, node);
	allocate_memory_for_filename_out(node);
	// Traitement des tokens pour les noms de fichiers
	// process_tokens_for_filenames(*tokens, node);
	// Traitement des tokens HEREDOC_TOKEN
	process_heredoc_tokens(*tokens, node);
	node->limiter_hd[node->limiter_hd_count] = NULL;
	// Traitement des tokens REDIR_IN
	process_filename_in(*tokens, node);
	node->filename_in[node->file_in_count] = NULL;
	// Traitement des tokens REDIR_OUT
	process_filename_out(*tokens, node);
	node->filename_out[node->file_out_count] = NULL;
}

void	parse_tokens(t_token *tokens, t_node *node)
{
	if (!tokens)
	{
		return ;
	}
	init_parsing(node);
	set_filename(&tokens, node);
	// SET ARGS and command
	init_args(tokens, node);
	set_cmd(tokens, node);
	// SET EXPANSION
	process_expansions(&tokens, node);
	// UPDATE NODE
	update_tokens(&tokens, node);
	// SET ARGS
	fill_args(tokens, node);
		//t_node	*head;
	// int		i;

	// head = node;
	// i = 0;
	// while (head)
	// {
	// 	printf("Node : %s\n", (char *)head->content);
	// 	printf("Cmd : %s\n", head->cmd);
	// 	while (i < node->file_in_count)
	// 	{
	// 		if (head->filename_in)
	// 			printf("File name in: %s\n", head->filename_in[i++]);
	// 	}
	// 	i = 0;
	// 	while (i < node->file_out_count)
	// 	{
	// 		if (head->filename_out)
	// 			printf("File name out: %s\n", head->filename_out[i++]);
	// 	}
	// 	i = 0;
	// 	while (i < node->limiter_hd_count)
	// 	{
	// 		if (head->limiter_hd)
	// 			printf("Here doc file: %s\n", head->limiter_hd[i++]);
	// 	}
	// 	int x = 0;
	// 	while (x < head->arg_count)
	// 	{
	// 		printf("Arg[x] : %s\n", head->args[x++]);
	// 	}
	// 	head = head->next;
	// }
}

	// DEBUG

	// t_node	*head;
	// int		i;

	// head = node;
	// i = 0;
	// while (head)
	// {
	// 	printf("Node : %s\n", (char *)head->content);
	// 	// printf("Cmd : %s\n", head->cmd);
	// 	// printf("File name out: %s\n", head->filename_out);
	// 	while (i < node->limiter_hd_count)
	// 	{
	// 		if (head->filename_in)
	// 			printf("File name in: %s : %s\n", head->limiter_hd[i],
	// 				head->filename_in);
	// 		printf("File name heredoc: %s\n", head->limiter_hd[i++]);
	// 	}
	// 	// printf("Node expansion: %s\n", head->key_expansion);
	// 	// printf("Arg cunt : %d\n", head->arg_count);
	// 	// int x = 0;
	// 	// while (x < head->arg_count)
	// 	// {
	// 	// 	printf("Arg[x] : %s\n", head->args[x++]);
	// 	// }
	// 	head = head->next;
	// }
