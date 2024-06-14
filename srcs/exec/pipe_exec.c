/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:07:38 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/14 12:18:35 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipes(int num_commands, int **pipes)
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

void	close_pipes_and_wait(int num_commands, int **pipes)
{
	int	i;

	i = 0;
	while (i < num_commands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	init_pipes(t_minishell *data, t_node *nodes)
{
	int i;

	i = 0;
	data->command_count = count_cmds(nodes);
	data->pipes = malloc(sizeof(int *) * data->command_count - 1);
	if (!data->pipes)
		return ;
	while (i < data->command_count - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	create_pipes(data->command_count, data->pipes);
}

void	exec_pipeline(t_node *nodes, t_minishell *data)
{
	t_node	*current_node;
	int		i;

	init_pipes(data, nodes);
	current_node = nodes;
	i = 0;
	while (i < data->command_count)
	{
		if (i == 0)
			current_node->fd_in = STDIN_FILENO;
		else
			current_node->fd_in = data->pipes[i - 1][0];
		if (i == data->command_count - 1)
			current_node->fd_out = STDOUT_FILENO;
		else
			current_node->fd_out = data->pipes[i][1];
		 exec_simple_cmd(data, current_node, get_cmd_path(current_node->cmd, data));
		if (current_node->fd_in != STDIN_FILENO)
			close(current_node->fd_in);
		if (current_node->fd_out != STDOUT_FILENO)
			close(current_node->fd_out);
		current_node = current_node->next;
		i++;
	}
	close_pipes_and_wait(data->command_count, data->pipes);
}
