#include "../../../includes/minishell.h"

char *expand_exit_status(char *str, int error_num)
{
	char *pos;
	size_t leading_len;
	size_t trailing_len;
	char *error_num_str;
	char *expanded;

	pos = ft_strstr(str, "$?");
	if (!pos)
        return ft_strdup(str);
    leading_len = pos - str;
    trailing_len = ft_strlen(pos + 2);
   	error_num_str = ft_itoa(error_num);
    if (!error_num_str)
		return (NULL);
	expanded = (char *)malloc(leading_len + ft_strlen(error_num_str) + trailing_len + 1);
	if (!expanded)
    {
        free(error_num_str);
        return NULL;
    }
    ft_strncpy(expanded, str, leading_len);
    ft_strcpy(expanded + leading_len, error_num_str);
    ft_strcpy(expanded + leading_len + ft_strlen(error_num_str), pos + 2);
    free(error_num_str);
    return expanded;
}

void process_token(t_token *tok, t_node *node, t_minishell *mini, int *arg_index)
{
	char *expanded_value;
	
	if (ft_strstr(tok->value, "$?") != NULL)
	{
		// UPDATE node->error_num : node->error_num = function in exec catching the error, 0 if no error 5default)
		expanded_value = expand_exit_status(tok->value, node->error_num);
		if (!expanded_value)
			return;
		node->args[*arg_index] = expanded_value;
	}
	else if (ft_strstr(tok->value, "$SHLVL") != NULL)
	{
		//UPDATE node->shlvl_num : node->shlvl_num = function in exec catching the shell level change, set to 1 by default
		expanded_value = expand_exit_status(tok->value, node->shlvl_num);
		if (!expanded_value)
			return;
		node->args[*arg_index] = expanded_value;
	}
	else if (tok->key_expansion != NULL)
		node->args[*arg_index] = get_expansion(mini, tok->key_expansion);
	else
		node->args[*arg_index] = ft_strdup(tok->value);
	if (!node->args[*arg_index])
	{
		while (*arg_index > 0)
			free(node->args[--(*arg_index)]);
		free(node->args);
		free(node->cmd);
		node->args = NULL;
		node->cmd = NULL;
		return;
	}
	(*arg_index)++;
}

void fill_args(t_token *tokens, t_node *node, t_minishell *mini)
{
	t_token *tok;
	int i;

	tok = tokens;
	if (!tokens || !node)
		return;
	if (node->lonely_expansion == 1)
	{
		node->args[0] = get_expansion(mini, tok->key_expansion);
		node->args[1] = NULL;
		return ;
	}
	i = 0;
	while (tok)
	{
		if (tok->type == TOKEN_WORD && !tok->processed)
		{
			process_token(tok, node, mini, &i);
			if (!node->args)
				return;
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
	if (node->filenames != NULL)
		node->filenames[node->file_count] = NULL;
	if (node->limiter_hd != NULL)
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

void check_lonely_expansions(t_token *tokens, t_node *node)
{
	t_token *tok;
	int i;

	tok = tokens;
	if (!tokens || !node)
		return;
	i = 0;
	while (tok && i < 1)
	{
		if (tok->key_expansion != NULL)
			node->lonely_expansion = 1;
		i++;
	}
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
	// CHECK LONELY
	check_lonely_expansions(tokens, node);
	// printf("is lonely : %d\n", node->lonely_expansion);
	// t_token *tok;
	// tok = tokens;
	// while (tok)
	// {
	// 	printf("token : %s\n", (char *)tok->value);
	// 	printf("expansion : %s\n", (char *)tok->key_expansion);
	// 	tok = tok->next;
	// }
	
	// GET EXPANSION from tokens
	set_expansions(tokens, node);
	//SET ARGS

	fill_args(tokens, node, mini);
	// t_node *head = node;
	// while (head)
	// {
	// 	printf("Node : %s\n", (char *)head->content);
	// 	printf("is lonely : %d\n", node->lonely_expansion);
	// 	printf("Cmd : %s\n", head->cmd);
	// 	printf("File name out: %s\n", head->filename_out);
	// 	printf("Node expansion: %s\n", head->key_expansion);
	// 	printf("Arg cunt : %d\n", head->arg_count);
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