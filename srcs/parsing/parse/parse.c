#include "../../../includes/minishell.h"

int	tokenizer(char *line, t_list **nodes, t_minishell *mini)
{
	t_list	*current;
	t_token	*tokens;
	char	*input;

	input = NULL;
	(void)mini;
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
		parse_tokens(tokens);
		current->tokens_in_node = tokens;
		current = current->next;
	}
	line = input; // free (input); ?
	return (1);
}

void	init_minishell(t_minishell *mini)
{
	mini->env = NULL;
	mini->nodes = NULL;
	mini->exit = 0;
	// a remplir au fur et a mesure
}
int	is_space(char *line)
{
	int	a;

	a = 0;
	while (line[a] == ' ' || line[a] == '\t' || line[a] == '\n')
		a += 1;
	if (line[a] == '\0')
		return (1);
	return (0);
}
int	check_line(char **line)
{
	if (*line[0] == '\0' || is_space(*line) || ft_strncmp(*line, "\n", 0))
		return (1);
	return (0);
}
// Segfault on free functions

int	main(int argc, char *argv[], char *env[])
{
	char		*input_line;
	t_list		*tokens_list;
	t_minishell	data;
	int			flag;
	t_list		*current;
	char		cwd[PATH_MAX];

	input_line = NULL;
	tokens_list = NULL;
	flag = 1;
	(void)argc;
	(void)argv;
	init_minishell(&data);
	if (!init_env(&data, env))
		return (1);
	// PRINT ENV
	// print_env(data.env);
	// Main shell execution Loop
	while (1)
	{
		getcwd(cwd, PATH_MAX);
		input_line = readline(ft_strjoin(cwd, " $> "));
		if (!input_line) // ctrl d
		{
			rl_clear_history(); // ?
			// return (0);
			break ;
		}
		if (check_line(&input_line))
		{
			free(input_line);
			continue ;
		}

		if (!tokenizer(input_line, &tokens_list, &data))
		{
			add_history(input_line);
			free(input_line);
			//return (0);
			continue;
		}
		add_history(input_line);
		current = tokens_list;		
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
		exec(current, &data);
		if (data.exit) // free all
		{
			//return (0);
			break;
		}
		// DEBUG
		// printf("current: %s\n", current->tokens_in_node->cmd);

		// DEBUG

		ft_lstclear(&tokens_list, free);
		// Clear the list after processing
		free(input_line);
	}
    ft_lstclear(&tokens_list, free);
    free(input_line);
    free_minishell(&data);
	return (0);
}
