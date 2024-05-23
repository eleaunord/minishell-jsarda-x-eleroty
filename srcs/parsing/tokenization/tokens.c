#include "../../../includes/minishell.h"

int	tokenizer(char *line, t_list *tokens_list)
{
	t_list	*current;
	char	*input;

	// check syntax (?)
	if (open_quote_check(line))
	{
		free(line);
		return (1);
	}
	input = remove_quotes(line);
	// pipes_spaces.c : Trim spaces + split into pipes
	ft_split_pipes_spaces(input, &tokens_list);
	// quotes : trim quotes
	// Debug / check content of the linked list using print_list
	current = tokens_list;
	while (current != NULL)
	{
		printf("Node : %s\n", (char *)current->content);
		current = current->next;
	}
	//
	return (1);
}
void init_minishell(t_minishell *mini)
{
	mini->env = NULL;
	mini->nodes = NULL;
	// a remplir au fur et a mesure
}
int	main(int argc, char *argv[], char *env[])
{
	char *input_line;
	t_list *tokens_list;
	t_minishell *data;
	int flag;

	input_line = NULL;
	tokens_list = NULL;
	flag = 1;
	(void)argc;
	(void)argv;

	init_minishell(data);
	if (env == init_env(env, data))
	{
		free_minishell(data);
		return (1);
	}
	while (1)
	{
		input_line = readline("prompt> ");
		if (input_line == NULL)
		{
			rl_clear_history();
			// printf("exit\n");
			flag = 0;
			// handler_sigint(SIGTERM);
		}
		if (!tokenizer(input_line, tokens_list))
		{
			add_history(input_line);
			free(input_line);
			return (0);
		}
		add_history(input_line);
		free(input_line);
		// exec command
		// free_input(&minishell);
	}
	ft_lstclear(&tokens_list, free);
	free(input_line);
	free_minishell(data);
	return (0);
}