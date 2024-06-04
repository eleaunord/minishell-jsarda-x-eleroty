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

int	count_arguments(t_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == TOKEN_WORD)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	process_redirection(t_token **tokens)
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

char *remove_quotes_from_word(char *word)
{
    if (!word)
        return NULL;

    int len = strlen(word);
    char *result = (char *)malloc(len + 1);
    if (!result)
    {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    int i, j = 0;
    char quote = 0; // To keep track of the current quote character
    for (i = 0; i < len; i++)
    {
        if (word[i] == '"' || word[i] == '\'')
        {
            if (quote == 0)
            {
                // Starting a new quote block
                quote = word[i];
            }
            else if (quote == word[i])
            {
                // Ending the current quote block
                quote = 0;
            }
        }
        else
        {
            // Normal character, just copy it
            result[j++] = word[i];
        }
    }
    result[j] = '\0';
    return result;
}
// int new_word_token(char *input, t_token **tokens, int index)
// {
//     char    *word;
//     int     in_quotes;
//     char    quote_char;
//     int     word_start;
//     int     word_end;

//     in_quotes = 0;
//     quote_char = '\0';
//     word_start = index;

//     while (input[index] != '\0')
//     {
//         if (!in_quotes && (input[index] == ' ' || input[index] == '>' || input[index] == '<'))
//         {
//             break;
//         }
//         close_quote_check(&in_quotes, &in_quotes, NULL, input[index]);
//         index++;
//     }

//     // Only create a token if we have a non-empty word
//     if (index > word_start)
//     {
//         word_end = index;
//         // Remove quotes if present
//         char *temp_line = ft_strndup(input + word_start, word_end - word_start);
//         if (temp_line)
//         {
//             word = remove_quotes_from_word(temp_line);
//             free(temp_line);
//             if (word)
//             {
//                 add_token_to_list(tokens, new_token(TOKEN_WORD, word));
//                 free(word);
//             }
//         }
//     }

//     // Skip any trailing spaces after the current word token
//     while (input[index] == ' ')
//     {
//         index++;
//     }

//     return index;
// }
void	update_tokens(t_token **tokens)
{
	t_token	*tok;

	if (!tokens || !*tokens)
		return ;
	tok = *tokens;
	while (tok)
	{
		if (ft_strchr(tok->value, '$') != NULL && tok->key_expansion == NULL)
			tok->value = remove_dollar_sign(tok->value);
        //tok = new_word_token(tok);
		tok = tok->next;
	}
}

void	parse_tokens(t_token *tokens)
{
	int		arg_count;
	int		i;
	t_token	*tmp;
	// t_token	*temp;

	if (!tokens)
		return ;
	// Set the first token's value to cmd
	tokens->cmd = ft_strdup(tokens->value);
	if (!tokens->cmd)
		return ;
	// Process redirections first
	tokens->processed = 0;
	process_redirection(&tokens);
	tokens->key_expansion = NULL;
	process_expansions(&tokens);
	update_tokens(&tokens);
	// printf("PRINT HERE %s\n", tokens->key_expansion);
	// DEBUG
	// temp = tokens;
	// while (temp != NULL)
	// {
	// 	printf("TOKEN now: %s\n", temp->value);
	// 	// printf("TYPE now: %d\n", temp->type);
	// 	if (temp->key_expansion != NULL)
	// 		printf("Key expansion: %s\n", temp->key_expansion);
	// 	temp = temp->next;
	// }
	// Move to the next token for counting arguments
	tmp = tokens->next;
	arg_count = count_arguments(tmp);
	tokens->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!tokens->args)
	{
		free(tokens->cmd);
		return ;
	}
	// ok
	i = 0;
	tmp = tokens->next;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD && !tmp->processed)
		{
			tokens->args[i] = ft_strdup(tmp->value);
			if (!tokens->args[i])
			{
				// Handle strdup failure, free allocated memory
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
	// No need to free the original list since we are keeping all tokens intact
}
