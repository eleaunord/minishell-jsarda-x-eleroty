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

int init_args(t_token *tokens, t_node *node)
{
    int arg_count = count_arguments(tokens);
    node->args = (char **)ft_calloc(arg_count + 1, sizeof(char *));
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
	node->filename_in = NULL;
	node->here_doc = 0;
	node->limiter_hd = NULL;
	node->key_expansion = NULL;
}
void	update_tokens(t_token **tokens, t_node *node)
{
	t_token	*current;
	char	*dollar_sign_pos;
	char	*new_value;

	if (!tokens || !*tokens || !node)
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
			node->key_expansion = new_value;
		}
		current = current->next;
	}

    // Update the tokens in the linked list of nodes
    while (node)
    {
        node->tokens_in_node = *tokens;
        node = node->next;
    }
}
// Modify so that command cannot be file name

void set_cmd(t_token *tokens, t_node *node)
{
	t_token *tok = tokens;


	if (!tokens || !node)
		return;

	while (tok != NULL)
	{
		if (tok->type == TOKEN_WORD)
		{
			// Check if it's the first TOKEN_WORD after a redirection
			if (!tok->processed)
			{
				node->cmd = ft_strdup(tok->value);
				node->args[0] = ft_strdup(tok->value);
				if (!node->cmd)
					return;
				
				return;
			}
		}
		else if (tok->type >= APPEND_TOKEN && tok->type <= REDIR_IN_TOKEN)
		{
			// Mark that we've encountered a redirection
			tok->processed = 1;
		}
		tok = tok->next;
	}

	// If no command was found
	node->cmd = NULL;
	node->args[0] = NULL;
}

void fill_args(t_token *tokens, t_node *node)
{

	t_token *tok = tokens;

	if (!tokens || !node)
		return;

	int i = 0;
	while (tok)
	{
		if (tok->type == TOKEN_WORD && !tok->processed)
		{
			node->args[i] = ft_strdup(tok->value);

			if (!node->args[i])
			{
				while (i > 0)
				{
					free(node->args[--i]);
				}
				free(node->args);
				free(node->cmd);
				return;
			}
			i++;
		}
		tok = tok->next;
	}
}
// enlver filename des args
void parse_tokens(t_token *tokens, t_node *node)
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
	process_expansions(&tokens, node);
	// UPDATE NODE
	update_tokens(&tokens, node);
	// SET ARGS
	fill_args(tokens, node);
	
	t_node *head = node;
	while (head)
	{
		 printf("Node : %s\n", (char *)head->content);
		printf("Cmd : %s\n", head->cmd);
		printf("File name in: %s\n", head->filename_in);
		printf("File name out: %s\n", head->filename_out);
		printf("File name heredoc: %s\n", head->limiter_hd);
		printf("Node expansion: %s\n", head->key_expansion);
		printf("Arg cunt : %d\n", head->arg_count);
		int x = 0;
		while (x < head->arg_count)
		{
			printf("Arg[x] : %s\n", head->args[x++]);
		}
		head = head->next;
	}
}



