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

void	parse_tokens(t_token *tokens)
{
	int		arg_count;
	int		i;
	t_token	*tmp;
	t_token	*next;

	if (!tokens)
		return ;
	// Set the first token's value to cmd
	tokens->cmd = ft_strdup(tokens->value);
	if (!tokens->cmd)
		return ;
	// Move to the next token for counting arguments
	tmp = tokens->next;
	arg_count = count_arguments(tmp);
	// printf("ARG COUNT %d\n", arg_count);
	tokens->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!tokens->args)
	{
		free(tokens->cmd);
		return ;
	}
	i = 0;
	while (tmp && i < arg_count)
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
		tmp = tmp->next;
		i++;

	}
	tokens->args[arg_count] = NULL;
	// Free the original list except the first token since we need to preserve tokens->cmd
	tmp = tokens->next;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	tokens->next = NULL;

}
