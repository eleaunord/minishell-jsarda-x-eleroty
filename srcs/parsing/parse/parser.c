/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:01:01 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/31 18:17:33 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_full_expansion(t_minishell *mini, char *input)
// {
// 	char	*result;
// 	char	*expanded_value;
	
// 	result = expand_exit_status(input);
// 	if (!result)
// 	{
// 		return (NULL);
// 	}
// 	expanded_value = get_expansion(mini, result);
// 	free(result);
// 	return (expanded_value);
// }

// void	process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
// {
// 	if (!node->args || *i >= node->arg_count)
// 		return ;
// 	if (tok->key_expansion != NULL)
// 	{
// 		node->args[*i] = get_full_expansion(mini, tok->key_expansion);
// 	}
// 	else
// 	{
// 		node->args[*i] = get_full_expansion(mini, tok->value);
// 	}
// 	if (!node->args[*i])
// 	{
// 		clear_process(node, i);
// 	}
// 	(*i)++;
// }



// // Helper function to count the number of words in the string
// static int count_words(const char *str, char delimiter)
// {
//     int count = 0;
//     int in_word = 0;

//     while (*str)
//     {
//         if (*str == delimiter)
//         {
//             in_word = 0;
//         }
//         else if (!in_word)
//         {
//             in_word = 1;
//             count++;
//         }
//         str++;
//     }
//     return count;
// }

// // Helper function to allocate a word
// static char *allocate_word(const char *start, const char *end)
// {
//     size_t length = end - start;
//     char *word = (char *)malloc(length + 1);
//     if (word)
//     {
//         strncpy(word, start, length);
//         word[length] = '\0';
//     }
//     return word;
// }

// // Main function to split the string
// char **ft_split_str(const char *str, const char *delimiters)
// {
//     char **result;
//     int words_count;
//     const char *word_start;
//     int i = 0;

//     if (!str || !delimiters)
//         return NULL;

//     words_count = count_words(str, delimiters[0]); // Assume single delimiter
//     result = (char **)malloc((words_count + 1) * sizeof(char *));
//     if (!result)
//         return NULL;

//     while (*str)
//     {
//         while (*str && strchr(delimiters, *str))
//             str++;
//         if (*str)
//         {
//             word_start = str;
//             while (*str && !strchr(delimiters, *str))
//                 str++;
//             result[i] = allocate_word(word_start, str);
//             if (!result[i])
//             {
//                 // Handle memory allocation failure
//                 while (i > 0)
//                     free(result[--i]);
//                 free(result);
//                 return NULL;
//             }
//             i++;
//         }
//     }
//     result[i] = NULL;
//     return result;
// }

// void	process_tok_dq(char *str,  t_minishell *mini, t_node *node, int *i)
// {
// 	char **split_str;
// 	char	*expanded_value;
// 	int index = 0;

// 	if (!node->args || *i >= node->arg_count)
// 		return ;
	
// 	split_str = ft_split_str(str, " ");
// 	while (split_str[index])
// 	{
// 		if (get_content_env(&mini->env, split_str[index]) !=  NULL)
// 			node->args[*i] = get_content_env(&mini->env, split_str[index]);		
// 		if (ft_strstr(split_str[index], "$?") != NULL)
// 		{
// 			expanded_value = expand_exit_status(split_str[index]);
// 			if (!expanded_value)
// 				return ;
// 			node->args[*i] = expanded_value;
// 			if (node->cmd && ft_strcmp(node->cmd, "$?") == 0)
// 		{
// 			free(node->cmd);
// 			node->cmd = ft_strdup(expanded_value);
// 		}
// 		}
// 		else
// 			node->args[*i] = ft_strdup(split_str[index]);
// 		if (!node->args[*i])
// 		{
// 			clear_process(node, i);
// 		}
// 	}
// 	free_tab(split_str);
// }

// void	process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
// {
// 	char	*expanded_value;
// 	//char *str;


// 	if (!node->args || *i >= node->arg_count)
// 		return ;
// 	if (tok->key_expansion != NULL)
// 		node->args[*i] = get_expansion(mini, tok);		
// 	else if (ft_strstr(tok->value, "$?") != NULL)
// 	{
// 		expanded_value = expand_exit_status(tok->value);
// 		if (!expanded_value)
// 			return ;
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
void	process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
{
	char	*expanded_value;
	//char *str;


	if (!node->args || *i >= node->arg_count)
		return ;
	if (tok->key_expansion != NULL)
	{
		while (tok->key_expansion != NULL)
		{
			if (ft_strstr(tok->value, "$?") != NULL)
			{
				expanded_value = expand_exit_status(tok->value);
				if (!expanded_value)
					return ;
				node->args[*i] = expanded_value;
				if (node->cmd && ft_strcmp(node->cmd, "$?") == 0)
				{
					free(node->cmd);
					node->cmd = ft_strdup(expanded_value);
				}
			}
			else if (ft_strstr(tok->key_expansion, "?") != NULL)
				node->args[*i] = get_expansion(mini, tok);
			else
				node->args[*i] = ft_strdup(tok->value);
		}
		if (!node->args[*i])
		{
			clear_process(node, i);
		}
		return ;
	}
	else
		node->args[*i] = ft_strdup(tok->value);
	if (!node->args[*i])
	{
		clear_process(node, i);
	}
	(*i)++;
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
			//printf("tok expan:%s\n", tok->key_expansion);
			//printf("tok value:%s\n", tok->value);
			process_tok(tok, node, mini, &i);
			// printf("tok expan after:%s\n", tok->key_expansion);
			// printf("tok value after:%s\n", tok->value);
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
