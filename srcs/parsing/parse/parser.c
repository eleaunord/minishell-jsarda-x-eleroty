#include "../../../includes/minishell.h"

char *get_expansion(t_minishell *data, char *key_expansion)
{
    char *path_value;
    char *result;
    char *start;
    char *end;
    char *dollar_pos;

    find_key_start_end(key_expansion, &start, &end);

    dollar_pos = strchr(key_expansion, '$');
    char *key = extract_key(start, end, dollar_pos);

    path_value = get_path_value(data, key);
    free(key);

    if (!path_value)
        return NULL;

    result = construct_result(key_expansion, start, end, path_value);

    return result;
}

void fill_args(t_token *tokens, t_node *node, t_minishell *mini)
{
	t_token *tok;
	int i;

	tok = tokens;
	if (!tokens || !node)
		return;
	i = 0;
	while (tok)
	{
		if (tok->type == TOKEN_WORD && !tok->processed)
		{
			if (tok->key_expansion != NULL)
				node->args[i] = get_expansion(mini, tok->key_expansion);
			else
				node->args[i] = ft_strdup(tok->value);
			if (!node->args[i])
			{
				while (i > 0)
					free(node->args[--i]);
				free(node->args);
				free(node->cmd);
				return;
			}
			i++;
		}
		tok = tok->next;
	}
	node->args[i] = NULL;
}

// Fonction principale filename
void set_filename(t_token **tokens, t_node *node)
{
	t_token *tok;

	if (!tokens || !*tokens || !node)
		return;
	tok = *tokens;
	count_redirections(&tok, node);
	allocate_memory_for_filenames(node);
	allocate_memory_for_limiter_hd(node);
	process_filenames(*tokens, node);
	node->filenames[node->file_count] = NULL;
	node->limiter_hd[node->limiter_hd_count] = NULL;
	// OLD STRUCTURE WITH DIFF REDIR
	// count_heredocs(&tok, node);
	// // Allocation de mémoire pour limiter_hd
	// allocate_memory_for_limiter_hd(node);
	// // other redirections : in and out
	// count_redir_in(&tok, node);
	// allocate_memory_for_filename_in(node);
	// count_redir_out(&tok, node);
	// allocate_memory_for_filename_out(node);
	// Traitement des tokens pour les noms de fichiers
	// process_tokens_for_filenames(*tokens, node);
	// Traitement des tokens HEREDOC_TOKEN
	// process_heredoc_tokens(*tokens, node);
	// node->limiter_hd[node->limiter_hd_count] = NULL;
	// // Traitement des tokens REDIR_IN
	// process_filename_in(*tokens, node);
	// node->filename_in[node->file_in_count] = NULL;
	// // Traitement des tokens REDIR_OUT
	// process_filename_out(*tokens, node);
	// node->filename_out[node->file_out_count] = NULL;
}

void parse_tokens(t_token *tokens, t_node *node, t_minishell *mini)
{
	if (!tokens)
	{
		return;
	}
	init_parsing(node);
	set_filename(&tokens, node);
	// SET ARGS and command
	init_args(tokens, node);
	set_cmd(tokens, node);
	// SET EXPANSION
	process_expansions(&tokens);
	// UPDATE NODE

	update_tokens(&tokens, node);
	// GET EXPANSION from tokens
	set_expansions(tokens, node);
	// SET ARGS
	// t_token *tok;
	// tok = tokens;
	// while (tok)
	// {
	// 	printf("token : %s\n", (char *)tok->key_expansion);
	// 	tok = tok->next;
	// }
	fill_args(tokens, node, mini);
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