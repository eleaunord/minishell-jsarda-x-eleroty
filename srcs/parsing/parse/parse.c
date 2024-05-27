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
	input = remove_quotes(line);
	ft_split_pipes_spaces(input, nodes);
	current = *nodes;
	while (current != NULL)
	{
		tokens = tokenize_input(current->content);
		parse_tokens(tokens);
		// attach tokens to the current list node
		current->tokens_in_node = tokens;
		current = current->next;
	}
	return (1);
}

void	init_minishell(t_minishell *mini)
{
	mini->env = NULL;
	mini->nodes = NULL;
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

	input_line = NULL;
	tokens_list = NULL;
	flag = 1;
	(void)argc;
	(void)argv;
	init_minishell(&data);
	if (init_env(&data, env))
	{
		return (1);
	}
	// Main shell execution Loop
	while (1)
	{
		input_line = readline("prompt> ");
		if (!input_line)
		{
			rl_clear_history(); // ?
			break ;
		}
		if (check_line(&input_line))
			break ;
		if (!tokenizer(input_line, &tokens_list, &data))
		{
			add_history(input_line);
			free(input_line);
			return (0);
		}
		add_history(input_line);
		current = tokens_list;

		exec(current);
		// DEBUG
		// printf("current: %s\n", current->tokens_in_node->cmd);
		// printf("current: %s\n", current->tokens_in_node->args[0]);
		// //
		// while (current != NULL)
		// {
		// 	printf("NODE : %s\n", (char *)current->content);
		// 	printf("CMD : %s\n", (char *)current->tokens_in_node->cmd);
		// 	int i = 0;
		// NB CHANGE i pour test 
		// 	while (i < 5)
		// 		printf("ARGS : %s\n", (char *)current->tokens_in_node->args[i++]);
		// 	current = current->next;
		// }
		ft_lstclear(&tokens_list, free); // Clear the list after processing
		free(input_line);
		
		
	}		
	return (0);
}
