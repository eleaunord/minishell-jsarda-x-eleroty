/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:18:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/16 13:19:58 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
//		indicating an error. If so,
//			print an error message using perror() and exit the child process with a failure status.

// #Step 3: Waiting for the Child Process to Finish with waitpid()

// 1 . Call waitpid() Function: In the parent process block,
//		use the waitpid() function to wait for the child process to finish execution.

// 2 . Handle Errors: Check if waitpid() returns -1,
//		indicating an error. If so, print an error message
//		using perror() and exit the parent process with a
//		failure status.

// #Step 4: Handling possible errors for fork(),
//		execve(), and waitpid()

// 1 . Error Handling for fork()
//		If fork() returns -1, an error has occurred. Print
//		an error message using perror() and exit the
//		program with EXIT_FAILURE.

// 2 . Error Handling for execve()
//		If execve() returns -1 in the child process,
//		it indicates an error. Print an error message
//		using perror() and exit the child process
//		with EXIT_FAILURE.

// 3 . Error Handling for waitpid()
//		If waitpid() returns -1, an error has occurred.
//		Print an error message using perror() and exit
//		the parent process with EXIT_FAILURE.

// #Step 5: Handling Redirections

// 1 . Open the File:
//		Use open() to open the file with the appropriate
//		flags (O_WRONLY, O_CREAT, O_TRUNC).

// 2 . Redirect Standard Output:
//		Use dup2() to duplicate the file
//		descriptor to STDOUT_FILENO.

// 3 . Execute the Command:
//		Use execve() to execute the command, which will
//		now write its output to the specified file.

void	handle_redir(char *input_file, char *output_file, int append)
{
	int	fd;

	if (input_file)
	{
		fd = open(input_file, O_RDONLY);
		if (fd < 0)
			perror_handler("open input file");
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			close(fd);
			perror_handler("dup2 input file");
		}
		close(fd);
	}
	if (output_file)
	{
		if (append)
			fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror_handler("open output file");
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			close(fd);
			perror_handler("dup2 input file");
		}
		close(fd);
	}
}

void	exec_cmd(char *path, char **argv, char *input_file, char *output_file,
		int append)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror_handler("fork");
	else if (pid == 0)
	{
		handle_redir(input_file, output_file, append);
		if (execve(path, argv, NULL) == -1)
			perror_handler("execve");
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror_handler("waitpid");
		if (WIFEXITED(status))
			printf("Child exited with status %d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("Child was killed by signal %d\n", WTERMSIG(status));
	}
}

// int	main(void)
// {
// 	char	*path;
// 	char	*argv[] = {"cat", "exec_cmd.c", NULL};
// 	char	*output_file;
// 	int		append;

// 	char *input_file = "test.txt";
// 	output_file = NULL;
// 	append = 0;
// 	path = "/bin/cat";
// 	exec_cmd(path, argv, input_file, output_file, append);
// }
