/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:07:38 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/19 15:26:12 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_mid_fd(t_node *cmd_lst, int *fd_temp, t_minishell *data)
{
	if (cmd_lst->fd_in == 0)
		cmd_lst->fd_in = *fd_temp;
	if (cmd_lst->fd_out == 1)
	{
		close(data->nodes->pipes[0]);
		cmd_lst->fd_out = data->nodes->pipes[1];
	}
}

void	exec_mid(t_node *cmd, t_minishell *data, t_node *prev)
{
	int		pid;
	char	**env;
	char	*path;

	path = NULL;
	env = NULL;
	if (pipe(cmd->pipes) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (prev)
			dup2(prev->pipes[0], STDIN_FILENO);
		if (cmd->next)
			dup2(cmd->pipes[1], STDOUT_FILENO);
		close(cmd->pipes[0]);
		close(cmd->pipes[1]);
		if (cmd->cmd && is_built_in(cmd) == -1)
		{
			env = create_char_env(data->env);
			path = get_cmd_path(cmd->cmd, data);
			if (execve(path, cmd->args, env) == -1)
			{
				perror("execve");
				fprintf(stderr, "minishell: %s: command not found\n",
					cmd->tokens_in_node->cmd);
				exit(EXIT_FAILURE);
			}
		}
		free_minishell(data, cmd);
		exit(EXIT_SUCCESS);
	}
	close(cmd->pipes[1]);
	if (prev)
		close(prev->pipes[0]);
}
void	exec_first(t_node *cmd, t_minishell *data)
{
	int		pid;
	char	**env;
	char	*path;

	env = NULL;
	path = NULL;
	if (pipe(cmd->pipes) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(cmd->pipes[1], STDOUT_FILENO);
		close(cmd->pipes[0]);
		close(cmd->pipes[1]);
		if (cmd->cmd && is_built_in(cmd) == -1)
		{
			env = create_char_env(data->env);
			path = get_cmd_path(cmd->cmd, data);
			if (execve(path, cmd->args, env) == -1)
			{
				perror("execve");
				fprintf(stderr, "minishell: %s: command not found\n",
					cmd->tokens_in_node->cmd);
				exit(EXIT_FAILURE);
			}
		}
		free_minishell(data, cmd);
		exit(EXIT_SUCCESS);
	}
	close(cmd->pipes[1]);
}

void	exec_last(t_node *cmd, t_minishell *data, t_node *prev)
{
	int		pid;
	char	**env;
	char	*path;

	env = NULL;
	path = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (prev)
			dup2(prev->pipes[0], STDIN_FILENO);
		if (cmd->cmd && is_built_in(cmd) == -1)
		{
			env = create_char_env(data->env);
			path = get_cmd_path(cmd->cmd, data);
			if (execve(path, cmd->args, env) == -1)
			{
				perror("execve");
				fprintf(stderr, "minishell: %s: command not found\n",
					cmd->tokens_in_node->cmd);
				exit(EXIT_FAILURE);
			}
		}
		free_minishell(data, cmd);
		exit(EXIT_SUCCESS);
	}
	if (prev)
		close(prev->pipes[0]);
}

void	exec_pipe(t_node *nodes, t_minishell *data)
{
	t_node	*current;
	t_node	*prev;

	prev = nodes;
	current = nodes;
	if (current)
	{
		exec_first(current, data);
		current = current->next;
	}
	while (current && current->next)
	{
		exec_mid(current, data, prev);
		prev = current;
		current = current->next;
	}
	if (current)
		exec_last(current, data, prev);
}
