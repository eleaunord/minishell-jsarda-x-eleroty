/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:18:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/27 13:54:57 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_built_in(t_list *list)
{
	if (ft_strncmp(list->tokens_in_node.cmd, "pwd", ft_strlen(list->tokens_in_node.cmd)) == 0)
		return (ft_pwd(), 0);
	if (ft_strncmp(list->tokens_in_node.cmd, "echo", ft_strlen(list->tokens_in_node.cmd)) != 0)
		return (ft_echo(list->tokens_in_node.args), 0);
	// if (ft_strncmp(list->cmd, "cd", ft_strlen(list->cmd)) != 0)
	// 		return (printf("here\n"), ft_cd(list->args, "srcs/"), 0);
	// if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) != 0)
	// 	return (ft_exit(), 0);
	// if (ft_strncmp(cmd, "env", ft_strlen(cmd)) != 0)
	// 	return (ft_env(), 0);
	// if (ft_strncmp(cmd, "export", ft_strlen(cmd)) != 0)
	// 	return (ft_export(), 0);
	// if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) != 0)
	// 	return (ft_unset(), 0);
	return (-1);
}

// void	handle_redir(t_redirection redir)
// {
// 	int	fd;

// 	if (redir.type == IN_REDIR)
// 	{
// 		fd = open(redir.file_name, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror("Error opening input file");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(fd, STDIN_FILENO) == -1)
// 		{
// 			perror("Error redirecting stdin");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(fd);
// 	}
// 	else if (redir.type == OUT_REDIR)
// 	{
// 		fd = open(redir.file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 		{
// 			perror("Error opening output file");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			perror("Error redirecting stdout");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(fd);
// 	}
// 	else if (redir.type == OUT_APPEND_REDIR)
// 	{
// 		fd = open(redir.file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 		{
// 			perror("Error opening output file");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			perror("Error redirecting stdout");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(fd);
// 	}
// 	// Note: HEREDOC_REDIR is not handled in this function.
// }

// void	redir_exec(t_list *list)
// {
// 	t_redirection	redirection;

// 	redirection = list->redirections;
// 	handle_redir(redirection);
// }

void	exec_simple_cmd(t_exec *exec, t_list *list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		// redir_exec(list);
		if (is_built_in(list) == - 1)
			if (execve("/bin/ls", exec->av, NULL) == -1)
				perror("execve");
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
		if (WIFEXITED(status))
			printf("Child exited with status %d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("Child was killed by signal %d\n", WTERMSIG(status));
	}
}

void	exec(t_list *list)
{
	t_exec	exec_struct;
	int		i;

	exec_struct.av = NULL;
	convert_to_exec_args(list, &exec_struct);
	if (exec_struct.av != NULL)
	{
		i = 0;
		exec_simple_cmd(&exec_struct, list);
		while (exec_struct.av[i] != NULL)
		{
			free(exec_struct.av[i]);
			i++;
		}
		free(exec_struct.av);
	}
}
