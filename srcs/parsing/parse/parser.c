#include "../../../includes/minishell.h"

/*
echo "'hey tu vas chew moi' 'non'" =>

	ARG[0]: 'hey
	ARG[1]: tu
	ARG[2]: vas
	ARG[3]: chez
	ARG[4]: moi'
	ARG[5]: 'non'
*/

<<<<<<< HEAD
int	count_arguments(t_token *tokens, t_token *cmd_token)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && tokens != cmd_token)
		{
			count++;
		}
		tokens = tokens->next;
=======
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
>>>>>>> parsing
	}
	return (count);
}

void	set_filename(t_token **tokens)
{
	t_token	*current;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	current->filename = NULL;
	while (current)
	{
		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				current->filename = current->next->value;
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
void init_parsing(t_token **tokens)
{
	t_token *current;
	current = *tokens;
	while (current)
	{
		current->processed = 0;
		current = current->next;
	}

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
		current = current->next;
	}
}

// enlver filename des args
void parse_tokens(t_token *tokens)
{
	int arg_count;
	int i;
	t_token *head = tokens;  // Keep the reference to the head of the list

	if (!tokens)
	{
		return;
	}
	init_parsing(&tokens);

	// FIRST TOKEN
	if (tokens->type >= APPEND_TOKEN && tokens->type <= REDIR_IN_TOKEN)
	{
		if (tokens->next && tokens->next->next)
		{
			tokens->cmd = ft_strdup(tokens->next->next->value);
			if (!tokens->cmd)
				return;
			tokens->next->next->processed = 1;
		}
		else
		{
			tokens->cmd = NULL;
		}
	}
	else if (tokens->type == TOKEN_WORD)
	{
		tokens->cmd = ft_strdup(tokens->value);
		tokens->processed = 1;
		if (!tokens->cmd)
			return;
	}
	else
		tokens->cmd = NULL;

	// SET FILENAME
	tokens->filename = NULL;
	set_filename(&tokens);

	// EXPAND
	tokens->key_expansion = NULL;
	process_expansions(&tokens);

	// UPDATE
	update_tokens(&tokens);

	// SET ARGS
	arg_count = count_arguments(tokens);
	//printf("ARG COUNT : %d\n", arg_count);
	head->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!head->args)
	{
		free(head->cmd);
		return;
	}
	i = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && !tokens->processed)
		{
			head->args[i] = ft_strdup(tokens->value);

			if (!head->args[i])
			{
				while (i > 0)
				{
					free(head->args[--i]);
				}
				free(head->args);
				free(head->cmd);
				return;
			}
			i++;
		}
		tokens = tokens->next;
	}
	head->args[arg_count] = NULL;  // Null-terminate the args array
}

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
