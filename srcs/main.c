/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:28:48 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 17:57:17 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=valgrind_readline_leaks_ignore.supp ./minishell

#include "minishell.h"

int		g_status = 0;

void	init_minishell(t_minishell *mini)
{
	mini->env = NULL;
	mini->env_dup = NULL;
	mini->nodes = NULL;
	mini->exit_status = 0;
}

int	main_loop(t_minishell *shell)
{
	char	*input_line;
	t_node	*node_list;

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
		g_status = 0;
		exec(shell);
		add_history(input_line);
		free(input_line);
		clear_nodes(&(shell->nodes));
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
