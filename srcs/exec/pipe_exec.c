/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:07:38 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/13 13:05:47 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmds(t_node *nodes)
{
	int		count;
	t_node	*current;

	count = 0;
	current = nodes;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	create_pipes(int num_commands, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < num_commands - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes_and_wait(int num_commands, int pipes[][2])
{
	int	i;

	i = 0;
	while (i < num_commands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < num_commands)
	{
		wait(NULL);
		i++;
	}
}

void	exec_pipeline(t_node *nodes, t_minishell *data)
{
	int		num_commands;
	t_node	*current_node;
	int		i;

	num_commands = count_cmds(nodes);
	int		pipes[num_commands - 1][2];
	create_pipes(num_commands, pipes);
	current_node = nodes;
	i = 0;

	while (i < num_commands)
	{
		if (i == 0)
			current_node->fd_in = STDIN_FILENO;
		else
			current_node->fd_in = pipes[i - 1][0];
		if (i == num_commands - 1)
			current_node->fd_out = STDOUT_FILENO;
		else
			current_node->fd_out = pipes[i][1];
		exec_simple_cmd(data, current_node, get_cmd_path(current_node->cmd,
				data));
		if (current_node->fd_in != STDIN_FILENO)
			close(current_node->fd_in);
		if (current_node->fd_out != STDOUT_FILENO)
			close(current_node->fd_out);
		current_node = current_node->next;
		i++;
	}
	close_pipes_and_wait(num_commands, pipes);
}
