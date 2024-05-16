/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:07:38 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/16 14:57:48 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// #Step 6: Handling Pipes

// 1 Create a Pipe: Use the pipe() system call to
//		create a pipe.

// 2 Redirect Output to the Pipe: In the first child
//		process, redirect STDOUT to the write end of the pipe.

// 3 Redirect Input from the Pipe: In the second
//		child process, redirect STDIN to the read end of the pipe.

// 4 Close Unused File Descriptors: Ensure that unused
//		file descriptors are closed in both the parent and child
//		processes.

// 5 Execute Commands: Execute the commands in the
//		respective child processes.

void	exec_pipe(char **cmd1, char **cmd2)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		perror_handler("pipe");
	pid1 = fork();
	if (pid1 < 0)
		perror_handler("fork");
	else if (pid1 == 0)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			perror_handler("dup2");
		close(pipefd[0]);
		close(pipefd[1]);
		if (execve(cmd1[0], cmd1, NULL) == -1)
			perror_handler("execve");
	}
	pid2 = fork();
	if (pid2 < 0)
		perror_handler("fork");
	else if (pid2 == 0)
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			perror_handler("dup2");
		close(pipefd[0]);
		close(pipefd[1]);
		if (execve(cmd2[0], cmd2, NULL) == -1)
			perror_handler("execve");
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (waitpid(pid1, &status, 0) == -1)
		perror_handler("waitpid pid1");
	if (waitpid(pid2, &status, 0) == -1)
		perror_handler("waitpid pid2");
}

// int	main(void)
// {
// 	char	*cmd1[] = {"/bin/ls", "-l", NULL};
// 	char	*cmd2[] = {"/usr/bin/wc", "-l", NULL};

// 	exec_pipe(cmd1, cmd2);
// 	return (0);
// }
