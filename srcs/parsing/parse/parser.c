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
			current->processed = 1;
			if (current->next && current->next->type == TOKEN_WORD)
				current->filename = current->next->value;
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
void	parse_tokens(t_token *tokens)
{
	int		arg_count;
	int		i;
	t_token	*tmp;
	t_token	*cmd_token;

	cmd_token = NULL;
	if (!tokens)
		return ;
	if (tokens->type >= 1 && tokens->type <= 4)
	{
		tmp = tokens->next;
		if (tmp && tmp->next)
		{
			tmp = tmp->next;
			tokens->cmd = ft_strdup(tmp->value);
			cmd_token = tmp; // Mark this token as cmd_token
			if (!tokens->cmd)
				return ;
		}
		else
		{
			tokens->cmd = NULL;
		}
	}
	else
	{
		tokens->cmd = ft_strdup(tokens->value);
		cmd_token = tokens; // Mark this token as cmd_token
		if (!tokens->cmd)
			return ;
	}
	set_filename(&tokens);
	tokens->key_expansion = NULL;
	process_expansions(&tokens);
	tokens->processed = 0;
	update_tokens(&tokens);
	tmp = tokens->next;
	arg_count = count_arguments(tmp, cmd_token);
	printf("ARG COUNT %d\n", arg_count);
	tokens->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!tokens->args)
	{
		free(tokens->cmd);
		return ;
	}
	i = 0;
	tmp = tokens->next;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD && !tmp->processed && tmp != cmd_token)
		{
			tokens->args[i] = ft_strdup(tmp->value);
			if (!tokens->args[i])
			{
				while (i > 0)
				{
					free(tokens->args[--i]);
				}
				free(tokens->args);
				free(tokens->cmd);
				return ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	tokens->args[arg_count] = NULL;
}

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
