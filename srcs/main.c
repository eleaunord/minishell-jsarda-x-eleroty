// valgrind --suppressions=valgrind_readline_leaks_ignore.supp ./minishell

#include "minishell.h"

int				g_status = 0;

void	init_minishell(t_minishell *mini)
{
	mini->env = NULL;
	mini->env_dup = NULL;
	mini->nodes = NULL;
	mini->exit_status = 0;
}
void	execute_commands(t_node *node_list, t_minishell *data)
{
	t_node	*head;

	head = node_list;
	exec(data);
	// if (data->exit)
	// {
	// 	free_nodes(node_list);
	// 	exit(data->exit_status);
	// }
	free_nodes(node_list);
}
int	main_loop(t_minishell *shell)
{
    char		*input_line;
    t_node		*node_list;

	input_line = NULL;
	node_list = NULL;
	while (1)
	{
		setup_signal_handlers();
		input_line = readline("prompt > ");
		if (!input_line)
		{
			rl_clear_history();
			break ;
		}
		if (!process_input_line(input_line, &node_list, shell))
			continue ;

		shell->exit_status = 0;
		add_history(input_line);
		debug_print_block(&node_list);
		exec(shell);
		//execute_commands(node_list, shell);
		free(input_line);
	}
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*mini;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(struct s_minishell));
	if (!mini)
		return (1);
	init_minishell(mini);
	if (!init_env(mini, env) || !init_env_dup(mini, env))
	{
		free(mini);
		return (1);
	}
    main_loop(mini);
	free_mini(mini);
	return (0);
}
// int	main(int argc, char *argv[], char *env[])
// {
// 	t_minishell	mini;

// 	(void)argc;
// 	(void)argv;
// 	init_minishell(&mini);
// 	if (!init_env(&mini, env) || !init_env_dup(&mini, env))
// 	{
// 		return (1);
// 	}
//     loop_shell(&mini);
// 	free_mini(&mini);
// 	return (0);
// }

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

// int i = 0;
// while (i < head->file_count)
// {
// 	printf("file name in order : %s at index : %d\n", head->filenames[i], i);
// 	i++;
// }
// i = 0;
// while (i < head->limiter_hd_count)
// {
// 	printf("file name in order : %s at index : %d\n", head->limiter_hd[i], i);
// 	i++;
// }
// i = 0;
// while (i < head->file_out_count)
// 	printf("file name OUT : %s\n", head->filename_out[i++]);
// i = 0;
// while (i < head->limiter_hd_count)
// 	printf("name EOF : %s\n", head->limiter_hd[i++]);
