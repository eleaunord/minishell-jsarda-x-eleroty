#include "../../../includes/minishell.h"
#include <stdbool.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (end > start && ft_strchr(set, *end))
		end--;
	return (ft_substr(start, 0, end - start + 1));
}

int	count_arguments(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD && !current->processed)
		{
			count++;
		}
		current = current->next;
	}
	return (count);
}

int set_args(t_token *tokens, t_node *node)
{
    int arg_count = count_arguments(tokens);
    node->args = (char **)calloc(arg_count + 1, sizeof(char *));
	node->arg_count = arg_count;
    if (!node->args)
    {
        free(node->cmd);
        return -1;
    }
    return 0;
}


// void	set_filename(t_token **tokens)
// {
// 	t_token	*current;

// 	if (!tokens || !*tokens)
// 		return ;
// 	current = *tokens;
// 	current->filename = NULL;
// 	while (current)
// 	{
// 		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
// 		{
// 			if (current->next && current->next->type == TOKEN_WORD)
// 			{
// 				current->filename = current->next->value;
// 				current->next->processed = 1;
// 			}
// 		}
// 		current = current->next;
// 	}
// }

void	set_filename(t_token **tokens, t_node *node)
{
	t_token	*current;

	if (!tokens || !*tokens || !node)
		return ;
	current = *tokens;
	while (current)
	{
		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				if (current->type == REDIR_IN_TOKEN)
					node->filename_in = current->next->value;
				else if (current->type == REDIR_OUT_TOKEN)
					node->filename_out = current->next->value;
				else if (current->type == HEREDOC_TOKEN)
				{
					node->here_doc = 1;
					node->limiter_hd = current->next->value;
				}
				current->next->processed = 1;
			}
		}
		current = current->next;
	}
}

char	*remove_dollar_sign(char *str)
{
	char	*new_str;
	char	*ptr;

	new_str = ft_strdup(str);
	ptr = ft_strchr(new_str, '$');
	if (ptr != NULL)
	{
		ft_strcpy(ptr, ptr + 1);
	}
	return (new_str);
}

char	*remove_quotes_from_word(char *word)
{
	int		len;
	char	*result;

	if (!word)
		return (NULL);
	len = strlen(word);
	result = (char *)malloc(len + 1);
	if (!result)
	{
		fprintf(stderr, "Memory allocation error\n");
		return (NULL);
	}
	int i, j = 0;
	char quote = 0; // To keep track of the current quote character
	for (i = 0; i < len; i++)
	{
		if (word[i] == '\'' && quote == 0)
		{
			// Starting or ending a single quote block
			while (word[++i] != '\'' && i < len)
			{
				result[j++] = word[i];
			}
		}
		else if (word[i] == '"' && quote == 0)
		{
			// Starting a double quote block
			quote = '"';
		}
		else if (word[i] == '"' && quote == '"')
		{
			// Ending a double quote block
			quote = 0;
		}
		else if (quote == '"' && (word[i] == '\\' || word[i] == '$'
				|| word[i] == '`'))
		{
			// Inside double quotes, special handling for \, $, and `
			result[j++] = word[i];
		}
		else
		{
			// Normal character, just copy it
			result[j++] = word[i];
		}
	}
	result[j] = '\0';
	return (result);
}
void init_parsing(t_node *node)
{
	// From parsing to exec
	node->args = NULL;
	node->arg_count = 0;
	node->cmd = NULL;
	node->filename_out = NULL;
	node->fd_out = 0;
	node->filename_in = NULL;
	node->fd_in = 0;
	node->here_doc = 0;
	node->limiter_hd = NULL;
	// // REDIRECTIONS
	// char				*filename; 
	// int					processed;
	// // EXPANSIONS
	// char				*key_expansion;

}
void	update_tokens(t_token **tokens)
{
	t_token	*current;
	char	*dollar_sign_pos;
	char	*new_value;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		// Check if the dollar sign is directly followed by a quote
		dollar_sign_pos = ft_strchr(current->value, '$');
		if (dollar_sign_pos != NULL && (*(dollar_sign_pos + 1) == '\''
				|| *(dollar_sign_pos + 1) == '"'))
		{
			current->value = remove_dollar_sign(current->value);
		}
		if (ft_strchr(current->value, '\'') != NULL || ft_strchr(current->value,
				'"') != NULL)
		{
			new_value = remove_quotes_from_word(current->value);
			free(current->value);
			current->value = new_value;
		}
		// New condition: Check if key_expansion is not NULL and is surrounded by double quotes
		if (current->key_expansion != NULL &&
			current->key_expansion[0] == '"' &&
			current->key_expansion[strlen(current->key_expansion) - 1] == '"')
		{
			// Trim the double quotes from key_expansion
			new_value = ft_strtrim(current->key_expansion, "\"");
			free(current->key_expansion);
			current->key_expansion = new_value;
		}
		current = current->next;
	}
}
// Modify so that command cannot be file name

void set_cmd(t_token *tokens, t_node *node)
{
	t_token *tok = tokens;
	int flag = 0;

	if (!tokens || !node)
		return;

	while (tok != NULL)
	{
		if (tok->type == TOKEN_WORD)
		{
			// Check if it's the first TOKEN_WORD after a redirection
			if (flag == 1)
			{
				node->cmd = ft_strdup(tok->value);
				node->args[0] = ft_strdup(tok->value);
				if (!node->cmd)
					return;
				tok->processed = 1;
				return;
			}
			else if (flag == 0)
			{
				// The list doesn't start with a redirection
				node->cmd = ft_strdup(tok->value);
				node->args[0] = ft_strdup(tok->value);
				tok->processed = 1;
				if (!node->cmd)
					return;
				return;
			}
		}
		else if (tok->type >= APPEND_TOKEN && tok->type <= REDIR_IN_TOKEN)
		{
			// Mark that we've encountered a redirection
			flag = 1;
		}
		tok = tok->next;
	}

	// If no command was found
	node->cmd = NULL;
	node->args[0] = NULL;
}




// enlver filename des args
void parse_tokens(t_token *tokens, t_node *node)
{
	//int arg_count;
	// int i;
	//t_token *head = tokens;  // Keep the reference to the head of the list
	// int flag = 0;

	if (!tokens)
	{
		return;
	}
	init_parsing(node);
	set_filename(&tokens, node);
	// SET ARGS
	set_args(tokens, node);
	set_cmd(tokens, node);
	while (node)
	{
		printf("Cmd : %s\n", node->cmd);
		printf("Arg[0] : %s\n", node->args[0]);
		node = node->next;
	}
	}
	// // SET FILENAME
	// tokens->filename = NULL;
	// set_filename(&tokens);
	// // FIRST TOKEN
	// t_token *tok = tokens;
	// if (tok->type >= APPEND_TOKEN && tok->type <= REDIR_IN_TOKEN)
	// {
	// 	t_token *next_token = tok->next; // filename

	// 	while (next_token != NULL)
	// 	{
	// 		if (next_token->next->type == TOKEN_WORD && next_token->filename == NULL)
	// 		{
	// 			tok->cmd = ft_strdup(next_token->next->value);
	// 			if (!tokens->cmd)
	// 				return;
	// 			next_token->next->processed = 1;
	// 			flag++;
	// 			break ;
	// 		}
	// 		next_token = next_token->next;
	// 	}
	// 	if (flag == 0)
	// 	{
	// 		tok->cmd = NULL;
	// 	}
	// }
	// else if (tok->type == TOKEN_WORD) // first token is cmd
	// {
	// 	tok->cmd = ft_strdup(tok->value); // LEAK
	// 	tok->processed = 1;
	// 	if (!tok->cmd)
	// 		return;
	// }
	// else
	// 	tok->cmd = NULL;



	// // EXPAND
	// tokens->key_expansion = NULL;
	// process_expansions(&tokens);

	// // UPDATE
	// update_tokens(&tokens);

	// // SET ARGS
	// arg_count = count_arguments(tokens);
	// head->args = ft_calloc(arg_count + 1, sizeof(char *));
	// if (!head->args)
	// {
	// 	free(head->cmd);
	// 	return;
	// }
	// i = 0;
	// while (tokens)
	// {
	// 	if (tokens->type == TOKEN_WORD && !tokens->processed)
	// 	{
	// 		head->args[i] = ft_strdup(tokens->value);

	// 		if (!head->args[i])
	// 		{
	// 			while (i > 0)
	// 			{
	// 				free(head->args[--i]);
	// 			}
	// 			free(head->args);
	// 			free(head->cmd);
	// 			return;
	// 		}
	// 		i++;
	// 	}
	// 	tokens = tokens->next;
	// }
// }

// DEBUG
// temp = tokens;
// printf("CMD : %s\n", temp->cmd);
// while (temp != NULL)
// {

// DEBUG
// temp = tokens;
// printf("CMD : %s\n", temp->cmd);
// while (temp != NULL)
// {

// 	printf("Token : %s\n", temp->value);
// 	printf("Type : %d\n", temp->type);
// 	if (temp->filename != NULL)
// 	{
// 		printf("Name of file: %s\n", temp->filename);
// 	}
// 	else
// 		printf("no file\n");
// 	if (temp->key_expansion != NULL)
// 	{
// 		printf("Key expansion: %s\n", temp->key_expansion);
// 	}
// 	else
// 		printf("no expansion\n");
// 	temp = temp->next;
// }

	// FILENAME DEBUG
	// while (node)
	// {
	// 	printf("f in : %s\n", node->filename_in);
	// 	printf("f out : %s\n", node->filename_out);
	// 	printf("limiter : %s\n", node->limiter_hd);
	// 	printf("hd : %d\n", node->here_doc);
	// 	node = node->next;
	// }