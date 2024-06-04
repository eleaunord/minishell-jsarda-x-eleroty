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

void process_redirection(t_token **tokens)
{
    t_token *current;

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


void parse_tokens(t_token *tokens)
{
    int arg_count;
    int i;
    t_token *tmp;

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
    printf("PRINT HERE %s\n", tokens->key_expansion);
    		// DEBUG 
		t_token *temp = tokens;
		while (temp != NULL)
		{
			printf("TOKEN now: %s\n", temp->value);
			// printf("TYPE now: %d\n", temp->type);
			if (temp->key_expansion != NULL)
				printf("Key expansion: %s\n", temp->key_expansion);
			temp = temp->next;
		}
    // Move to the next token for counting arguments
    tmp = tokens->next;
    arg_count = count_arguments(tmp);
    tokens->args = malloc(sizeof(char *) * (arg_count + 1));
    if (!tokens->args)
    {
        free(tokens->cmd);
        return ;
    }
	//ok
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
