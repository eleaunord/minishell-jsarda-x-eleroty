#include "../../../includes/minishell.h"

int tokenizer(char *line, t_node **nodes, t_minishell *mini)
{
	t_node *current;
	t_token *tokens;
	char *line_copy;
	bool error;

	if (open_quote_check(line))
		return (0);
	line_copy = ft_strdup(line);
	if (!line_copy)
		return (0);
	error = ft_split_pipes_spaces(line_copy, nodes);
	if (error)
	{
		write(1, "Syntax error\n", 13);
		free(line_copy);
		freelist(nodes);
		return (0);
	}
	free(line_copy);
	current = *nodes;
	mini->nodes = *nodes;
	while (current != NULL)
	{
		tokens = tokenize_input(current->content);
		if (!tokens)
		{
			freelist(nodes);
			mini->nodes = NULL;
			return (0);
		}
		parse_tokens(tokens, current, mini);
		free_tokens(tokens);
		current = current->next;
	}
	return (1);
}

int process_input_line(char *input_line, t_node **node_list, t_minishell *data)
{
    if (check_line(&input_line))
    {
        free(input_line);
        return 0;
    }
    if (!tokenizer(input_line, node_list, data))
    {
        add_history(input_line);
        free(input_line);
        return 0;
    }
	// t_node *current;
	// int i;
	// current = *node_list;
    // while (current != NULL)
    // {
    //     i = 0;
        
    //     while (current->args[i] != NULL)
    //     {
    //         printf("Node args[%d]: %s\n", i, current->args[i]);
    //         i++;
    //     }
    //     current = current->next;
    // }
    return 1;
}

