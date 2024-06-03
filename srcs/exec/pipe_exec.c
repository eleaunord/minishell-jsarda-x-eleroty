/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:07:38 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/03 12:06:24 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(char ***cmds, int i, int num_cmds, int *pipefd)
{
	int	j;

	if (i != 0)
	{
		if (dup2(pipefd[(i - 1) * 2], STDIN_FILENO) == -1)
			perror_handler("dup2");
	}
	if (i != num_cmds - 1)
	{
		if (dup2(pipefd[i * 2 + 1], STDOUT_FILENO) == -1)
			perror_handler("dup2");
	}
	j = 0;
	while (j < 2 * (num_cmds - 1))
	{
		close(pipefd[j]);
		j++;
	}
	if (execve(cmds[i][0], cmds[i], NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(int num_cmds, int *pipefd)
{
	int	i;
	int	status;

	i = 0;
	while (i < 2 * (num_cmds - 1))
	{
		close(pipefd[i]);
		i++;
	}
	i = 0;
	while (i < num_cmds)
	{
		if (wait(&status) == -1)
			perror_handler("wait");
		i++;
	}
}

void	exec_pipeline(char ***cmds, int num_cmds)
{
	int		i;
	int		pipefd[2 * (num_cmds - 1)];
	pid_t	pid;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipefd + 2 * i) == -1)
			perror_handler("pipe");
		i++;
	}
	i = 0;
	while (i < num_cmds)
	{
		pid = fork();
		if (pid == 0)
			child_process(cmds, i, num_cmds, pipefd);
		else if (pid < 0)
			perror_handler("fork");
		i++;
	}
	parent_process(num_cmds, pipefd);
}
