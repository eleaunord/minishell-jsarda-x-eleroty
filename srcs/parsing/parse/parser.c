/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:01:01 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 10:19:17 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// TO DO : tok->sq is not well set ; ca marche pas avec les singles quotes mtn

// void process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
// {
// 	char *expanded_value;

// 	if (!node->args || *i >= node->arg_count)
// 		return;
// 	if (tok->key_expansion != NULL)
// 		node->args[*i] = get_expansion(mini, tok);
// 	else if (ft_strstr(tok->value, "$?") != NULL)
// 	{
// 		expanded_value = expand_exit_status(tok->value);
// 		if (!expanded_value)
// 			return;
// 		node->args[*i] = expanded_value;
// 		if (node->cmd && ft_strcmp(node->cmd, "$?") == 0)
// 		{
// 			free(node->cmd);
// 			node->cmd = ft_strdup(expanded_value);
// 		}
// 	}
// 	else
// 		node->args[*i] = ft_strdup(tok->value);
// 	if (!node->args[*i])
// 	{
// 		clear_process(node, i);
// 	}
// 	(*i)++;
// }

// void process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
// {
// 	if (!node->args || *i >= node->arg_count)
// 		return;

// 	// Free previously allocated memory if any
// 	if (node->args[*i])
// 	{
// 		free(node->args[*i]);
// 		node->args[*i] = NULL;
// 	}

// 	char *original = tok->value;
// 	char *result = NULL;
// 	size_t result_len = 0;
// 	char *cur = original;

// 	while (*cur)
// 	{
// 		char *start = NULL;
// 		char *end = NULL;
// 		char *key = extract_key(cur, &start, &end);

// 		if (key)
// 		{
// 			size_t len_before_key = start - cur;
// 			size_t key_len = end - start;
// 			char *path_value = NULL;

// 			if (tok->sq != 1) // Check if tok->sq is not 1 before expanding
// 			{
// 				path_value = get_path_value(mini, key);
// 			}

// 			// Resize the result buffer
// 			size_t new_size = result_len + len_before_key + (path_value ? strlen(path_value) : key_len) + 1;
// 			char *new_result = realloc(result, new_size);
// 			if (!new_result)
// 			{
// 				free(result);
// 				free(key);
// 				return;
// 			}
// 			result = new_result;

// 			// Copy part before the key
// 			if (len_before_key > 0)
// 			{
// 				strncpy(result + result_len, cur, len_before_key);
// 				result_len += len_before_key;
// 			}

// 			// Copy the value of the key or the key itself if it's within single quotes
// 			if (path_value)
// 			{
// 				strcpy(result + result_len, path_value);
// 				result_len += strlen(path_value);
// 			}
// 			else
// 			{
// 				strncpy(result + result_len, start, key_len);
// 				result_len += key_len;
// 			}

// 			// Move the cursor
// 			cur = end;
// 			free(key);
// 		}
// 		else
// 		{
// 			size_t len_remaining = strlen(cur);
// 			char *new_result = realloc(result, result_len + len_remaining + 1);
// 			if (!new_result)
// 			{
// 				free(result);
// 				return;
// 			}
// 			result = new_result;
// 			strcpy(result + result_len, cur);
// 			result_len += len_remaining;
// 			break;
// 		}
// 	}

// 	// Handle the special case of expanding "$?"
// 	if (ft_strstr(result, "$?") != NULL)
// 	{
// 		char *expanded_value = expand_exit_status(result);
// 		if (expanded_value)
// 		{
// 			free(result);
// 			result = expanded_value;
// 			result_len = strlen(result);
// 		}
// 	}

// 	// Ensure result is null-terminated
// 	if (result)
// 	{
// 		result[result_len] = '\0';
// 	}

// 	node->args[*i] = result;

// 	if (!node->args[*i])
// 	{
// 		printf("node->args[%d] is NULL after processing\n", *i);
// 		clear_process(node, i);
// 		return;
// 	}

// 	printf("Set node->args[%d] to result: %s\n", *i, node->args[*i]);

// 	// Set node->cmd if it's the first argument
// 	if (*i == 0)
// 	{
// 		node->cmd = ft_strdup(result);
// 		printf("Set node->cmd to: %s\n", node->cmd);
// 	}

// 	(*i)++;
// 	printf("Incremented i to: %d\n", *i);
// }

void process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
{
    if (!node->args || *i >= node->arg_count)
        return;

    // Free previously allocated memory if any
    if (node->args[*i])
    {
        free(node->args[*i]);
        node->args[*i] = NULL;
    }

    // Check if the token is inside single quotes
    if (tok->sq == 1)
    {
		//printf("hey");
        node->args[*i] = strdup(tok->value);  // Store the value directly if inside single quotes
        if (!node->args[*i])
        {
            printf("node->args[%d] is NULL after storing tok->value\n", *i);
            clear_process(node, i);
            return;
        }
        printf("Set node->args[%d] to tok->value: %s\n", *i, node->args[*i]);

        // Set node->cmd if it's the first argument
        if (*i == 0)
        {
            node->cmd = ft_strdup(node->args[*i]);
        }

        (*i)++;
        printf("Incremented i to: %d\n", *i);
        return;
    }

    // If not inside single quotes, proceed with the expansion
    char *original = tok->value;
    char *result = NULL;
    size_t result_len = 0;
    char *cur = original;

    while (*cur)
    {
        char *start = NULL;
        char *end = NULL;
        char *key = extract_key(cur, &start, &end);

        if (key)
        {
            size_t len_before_key = start - cur;
            size_t key_len = end - start;
            char *path_value = get_path_value(mini, key);

            // Resize the result buffer
            size_t new_size = result_len + len_before_key + (path_value ? strlen(path_value) : key_len) + 1;
            char *new_result = realloc(result, new_size);
            if (!new_result)
            {
                free(result);
                free(key);
                return;
            }
            result = new_result;

            // Copy part before the key
            if (len_before_key > 0)
            {
                strncpy(result + result_len, cur, len_before_key);
                result_len += len_before_key;
            }

            // Copy the value of the key
            if (path_value)
            {
                strcpy(result + result_len, path_value);
                result_len += strlen(path_value);
            }
            else
            {
                strncpy(result + result_len, start, key_len);
                result_len += key_len;
            }

            // Move the cursor
            cur = end;
            free(key);
        }
        else
        {
            size_t len_remaining = strlen(cur);
            char *new_result = realloc(result, result_len + len_remaining + 1);
            if (!new_result)
            {
                free(result);
                return;
            }
            result = new_result;
            strcpy(result + result_len, cur);
            result_len += len_remaining;
            break;
        }
    }

    // Handle the special case of expanding "$?"
    if (ft_strstr(result, "$?") != NULL)
    {
        char *expanded_value = expand_exit_status(result);
        if (expanded_value)
        {
            free(result);
            result = expanded_value;
            result_len = strlen(result);
        }
    }

    // Ensure result is null-terminated
    if (result)
    {
        result[result_len] = '\0';
    }

    node->args[*i] = result;

    if (!node->args[*i])
    {
        printf("node->args[%d] is NULL after processing\n", *i);
        clear_process(node, i);
        return;
    }

    printf("Set node->args[%d] to result: %s\n", *i, node->args[*i]);

    // Set node->cmd if it's the first argument
    if (*i == 0)
    {
        node->cmd = ft_strdup(result);
    }

    (*i)++;
    printf("Incremented i to: %d\n", *i);
}


void	fill_args(t_token *tokens, t_node *node, t_minishell *mini)
{
	t_token	*tok;
	int		i;

	tok = tokens;
	if (!tokens || !node)
		return ;
	if (node->lonely_expansion == 1)
	{
		node->args[0] = get_expansion(mini, tok);
		node->cmd = get_expansion(mini, tok);
		node->args[1] = NULL;
		return ;
	}
	i = 0;
	while (tok)
	{
		if (tok->type == TOKEN_WORD && !tok->processed)
		{
			printf("tok value: %s\n", tok->value);
			process_tok(tok, node, mini, &i);
			
			if (!node->args)
				return ;
		}
		tok = tok->next;
	}
	node->args[i] = NULL;
}

void	set_filename(t_token **tokens, t_node *node)
{
	t_token	*tok;

	if (!tokens || !*tokens || !node)
		return ;
	tok = *tokens;
	count_heredocs(&tok, node);
	allocate_memory_for_limiter_hd(node);
	count_redir_in(&tok, node);
	allocate_memory_for_filename_in(node);
	count_redir_out(&tok, node);
	allocate_memory_for_filename_out(node);
	process_heredoc_tokens(*tokens, node);
	node->limiter_hd[node->limiter_hd_count] = NULL;
	process_filename_in(*tokens, node);
	process_filename_out(*tokens, node);
	node->filename_out[node->file_out_count] = NULL;
}

void	parse_tokens(t_token *tokens, t_node *node, t_minishell *mini)
{
	if (!tokens)
	{
		return ;
	}
	init_parsing(node);
	set_filename(&tokens, node);
	init_args(tokens, node);
	set_cmd(tokens, node);
	process_expansions(&tokens);
	update_tokens(&tokens, node);
	check_lonely_expansions(tokens, node);
	set_expansions(tokens, node);
	fill_args(tokens, node, mini);
}
