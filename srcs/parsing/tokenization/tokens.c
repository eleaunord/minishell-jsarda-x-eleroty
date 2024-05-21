#include "../../includes/minishell.h"


int	tokenizer(char *input, t_list *tokens_list)
{
	t_list	*current;

	// check syntax (?)

	// pipes_spaces : Trim spaces + split into pipes
	ft_split_pipes_spaces(input, &tokens_list);

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
int	main(int argc, char *argv[])
{
	char *input_line;
	t_list *tokens_list;
	int flag;

	input_line = NULL;
	tokens_list = NULL;
	flag = 1;
	(void)argc;
	(void)argv;

	// set_input(&minishell);
	while (flag == 1)
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
		return (1);
		// exec command
		// free_input(&minishell);
	}
	ft_lstclear(&tokens_list, free);
	free(input_line);
	return (0);
}