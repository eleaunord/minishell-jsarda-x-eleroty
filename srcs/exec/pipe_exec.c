/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:07:38 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/18 09:14:52 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	exec_mid(t_node *cmd, t_minishell *data)
// {
// 	t_node *mid_cmd;
// 	int pid;
// 	char *env;
// 	char path;

// 	path = NULL;
// 	env = NULL;
// 	mid_cmd = cmd;
// 	pipe(mid_cmd->pipes);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		manage_mid_fd();
// 		if (mid_cmd->cmd && is_built_in(cmd) == -1)
// 		{
// 			env = create_char_env(data->env);
// 			path = get_cmd_path(mid_cmd->cmd, data);
// 			dup2(mid_cmd->pipes[0], mid_cmd->pipes[1]);
// 			if (execve(path, mid_cmd->args, env) == -1)
// 			{
// 				perror("execve");
// 				fprintf(stderr, "minishell: %s: command not found\n",
// 					mid_cmd->tokens_in_node->cmd);
// 			}
// 		}
// 		// exit child
// 	}
// 	close(mid_cmd->pipes[1]);
// 	// close tmp fd
// 	// close fd in and out
// }
// void	exec_first(t_node *cmd)
// {

// }
// void exec_last(t_node *cmd, t_minishell *data)
// {
// 	t_node *last_cmd;
// 	char *path;
// 	int pid;
// 	char *env;

// 	path = NULL;
// 	last_cmd = cmd;
// 	env = NULL;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (last_cmd->fd_in == 0)
// 			last_cmd->fd_in = last_cmd->pipes[0];
// 		if (last_cmd->cmd && is_built_in(cmd) == -1)
// 		{
// 			env = create_char_env(data->env);
// 			path = get_cmd_path(last_cmd->cmd, data);
// 			dup2(last_cmd->pipes[0], last_cmd->pipes[1]);
// 			if (execve(path, last_cmd->args, env) == -1)
// 			{
// 				perror("execve");
// 				fprintf(stderr, "minishell: %s: command not found\n",
// 					last_cmd->tokens_in_node->cmd);
// 			}
// 		}
// 		// exit child
// 	}
// 	close(last_cmd->pipes[0]);
// 	// close fdin and out
// }
// void	exec_pipe(t_node *nodes, t_minishell *data)
// {
// 	t_node *current;

// 	current = nodes;
// 	if (current)
// 		exec_first(current);
// 	while (current->next)
// 		exec_mid(current, data);
// 	if (current->next == NULL)
// 		exec_last(current, data);
// }
