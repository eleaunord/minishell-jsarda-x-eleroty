/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:07:38 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/14 15:23:19 by jsarda           ###   ########.fr       */
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

void	create_pipes(int pipes[2])
{
	if (pipe(pipes) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_pipes_and_wait(int pipes[2], int num_commands)
{
	close(pipes[0]);
	close(pipes[1]);
	while (num_commands)
	{
		wait(NULL);
		num_commands--;
	}
}

void	exec_pipeline(t_node *nodes, t_minishell *data)
{
	int		num_commands;
	t_node	*current_node;
	int		i;
	int		pipes[2];

	num_commands = count_cmds(nodes);
	create_pipes(pipes);
	current_node = nodes;
	i = 0;
	int tmp_fd = -1;
	while (current_node)
	{
		if (i == 0)
			current_node->fd_in = STDIN_FILENO;
		else
		{
			printf("cmd 1= %s\n", current_node->cmd);
			current_node->fd_in = pipes[0];
		}
		if (i == num_commands - 1)
			current_node->fd_out = STDOUT_FILENO;
		else
		{
			printf("cmd 2= %s\n", current_node->cmd);
			if (tmp_fd == -1)
			{
				current_node->fd_out = pipes[1];
				tmp_fd = pipes[1];
			}
			else
				current_node->fd_out = tmp_fd;
		}
		exec_simple_cmd(data, current_node, get_cmd_path(current_node->cmd,
				data));
		if (current_node->fd_in != STDIN_FILENO)
			close(current_node->fd_in);
		if (current_node->fd_out != STDOUT_FILENO)
			close(current_node->fd_out);
		current_node = current_node->next;
		i++;
	}
	close_pipes_and_wait(pipes, num_commands);
}

// void	exec_first()
// void	exec_mid()
// void exec_last()
// void	exec_pipe()
// {
// 	if (le prenmier)
// 		exec_first
// 	while (its not the last)
// 		exec_mid
// 	if (le dernier)
// 		exec_last
// }
