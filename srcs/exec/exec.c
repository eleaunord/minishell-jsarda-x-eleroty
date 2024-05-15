/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:39:29 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/15 15:40:09 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

// #Step 1: Creating a Child Process with fork()

// 1. Call fork() Function: Use the fork() function to create
//		a new process. It returns a process ID (PID).

// 2. Check the Return Value of fork(): After calling fork(),
//		you should check its return value to determine
//		whether the process is the parent or the child.

// 3. Handle Errors: Check if fork() returns -1, indicating
//		an error. If so, print an error message using
//		perror() and exit the program.

// #Step 2: Replacing the Process Image with execve()

// 1 . Call execve() Function: In the child process block,
//		use the execve() function to replace the current process image with a new executable.
// 3 . Handle Errors: Check if execve() returns -1,
//		indicating an error. If so, print an error message using perror() and exit the child process with a failure status.

// #Step 3: Waiting for the Child Process to Finish with waitpid()

// 1 . Call waitpid() Function: In the parent process block,
//		use the waitpid() function to wait for the child process to finish execution.

// 2 . Handle Errors: Check if waitpid() returns -1,
//		indicating an error. If so, print an error message
//		using perror() and exit the parent process with a
//		failure status.

int	main(void)
{
	pid_t	pid;
	char	*path;
	char	*argv[] = {"cat", "exec.c", NULL};
	int status;

	path = "/bin/cat";
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("Child process created\n");
		if (execve(path, argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("Parent process: Child PID = %d\n", pid);
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		printf("Child process finished\n");
	}
	return (0);
}
