/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:07:38 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/20 13:52:44 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(t_node *cmd)
{
	int	i;

	i = 0;
	if (cmd->here_doc)
	{
		while (cmd->limiter_hd[i])
		{
			get_tmp_file(cmd);
			heredoc(cmd->limiter_hd[i], cmd->heredoc_filename);
			i++;
			if (cmd->limiter_hd[i])
				unlink(cmd->heredoc_filename);
		}
	}
}

void	handle_builtin(t_node *list, t_minishell *data)
{
	if (is_built_in(list) != -1)
	{
		if (check_if_redir(list) == 0 || list->here_doc == 1)
			handle_redir(list);
		exec_built_in(data, list);
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
	handle_heredoc(cmd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (prev)
		{
			dup2(prev->pipes[0], STDIN_FILENO);
			close(prev->pipes[0]);
		}
		if (cmd->next)
			dup2(cmd->pipes[1], STDOUT_FILENO);
		if (check_if_redir(cmd) == 0)
			handle_redir(cmd);
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
		else if (is_built_in(cmd) != -1)
			handle_builtin(cmd, data);
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
	handle_heredoc(cmd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(cmd->pipes[1], STDOUT_FILENO);
		if (check_if_redir(cmd) == 0)
			handle_redir(cmd);
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
		else if (is_built_in(cmd) != -1)
			handle_builtin(cmd, data);
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
	handle_heredoc(cmd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (prev)
		{
			dup2(prev->pipes[0], STDIN_FILENO);
			close(prev->pipes[0]);
		}
		if (check_if_redir(cmd) == 0)
			handle_redir(cmd);
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
		else if (is_built_in(cmd) != -1)
			handle_builtin(cmd, data);
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

	prev = NULL;
	current = nodes;
	if (current)
	{
		exec_first(current, data);
		prev = current;
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
	while (wait(NULL) > 0)
		;
}
