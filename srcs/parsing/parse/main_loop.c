#include "../../../includes/minishell.h"

int	tokenizer(char *line, t_node **nodes)
{
	t_node	*current;
	t_token	*tokens;
	char	*input;

	input = NULL;
	if (open_quote_check(line))
	{
		free(line);
		return (0);
	}
	input = ft_split_pipes_spaces(line, nodes);
	current = *nodes;
	while (current != NULL)
	{
		tokens = tokenize_input(current->content);
		parse_tokens(tokens, current);
		current = current->next;
	}
	line = input;
	return (1);
}

void	init_minishell(t_minishell *mini)
{
	mini->env = NULL;
	mini->nodes = NULL;
	mini->exit = 0;
}

int	main(int argc, char *argv[], char *env[])
{
	char		*input_line;
	t_node		*node_list;
	t_minishell	data;
	t_node *head_nodes;

	input_line = NULL;
	node_list = NULL;
	(void)argc;
	(void)argv;
	init_minishell(&data);
	if (!init_env(&data, env))
		return (1);
	while (1)
	{
		input_line = readline("prompt > ");
		if (!input_line)
		{
			rl_clear_history();
			break ;
		}
		if (check_line(&input_line))
		{
			free(input_line);
			continue ;
		}

		if (!tokenizer(input_line, &node_list))
		{
			add_history(input_line);
			free(input_line);
			continue;
		}
		add_history(input_line);
		head_nodes = node_list;
		//t_node *head = node_list;
		// while (head)
		// {
		// 	printf("Node : %s\n", (char *)head->content);
		// 	printf("Cmd : %s\n", head->cmd);
		// 	printf("File name in: %s\n", head->filename_in);
		// 	printf("File name out: %s\n", head->filename_out);
		// 	printf("File name heredoc: %s\n", head->limiter_hd);
		// 	printf("Node expansion: %s\n", head->key_expansion);
		// 	printf("Arg cunt : %d\n", head->arg_count);
		// 	int x = 0;
		// 	while (x < head->arg_count)
		// 	{
		// 		printf("Arg[x] : %s\n", head->args[x++]);
		// 	}
		// 	head = head->next;
		// }
		//exec(head, &data);
		if (data.exit)
		{
			break ;
		}
		head_nodes = NULL;
	}
    free(input_line);
    free_minishell(&data, head_nodes);
	return (0);
}


// DEBUG

	// PRINT ENV
	// print_env(data.env);
	// Main shell execution Loop


// DEBUG

		// while (current != NULL)
		// {
		// 	printf("NODE : %s\n", (char *)current->content);
		// 	t_token *temp = current->tokens_in_node;
		// 	printf("CMD : %s\n", temp->cmd);
		// 	while (temp != NULL)
		// 	{
		// 		printf("TOKEN : %s\n", temp->value);
		// 		printf("TYPE: %d\n", temp->type);
		// 		printf("cmd : %s\n", temp->cmd);
		// 		printf("file name : %s\n", temp->filename);
		// 		printf("key expansion : %s\n", temp->key_expansion);
		// 		int i = 0;
		// 		while (temp->args && i < count_arguments(temp))
		// 		{
		// 			printf("ARGS : %s\n", temp->args[i++]);
		// 		}
		// 		temp = temp->next;
		// 	}

		// 	current = current->next;
		// }
