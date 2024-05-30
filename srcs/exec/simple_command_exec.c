/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:18:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/30 12:23:06 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_built_in(t_list *list)
{
	int		i;
	char	*built_in[NUM_OF_BUILT_INS];

	built_in[0] = "pwd";
	built_in[1] = "echo";
	built_in[2] = "exit";
	i = 0;
	while (i < NUM_OF_BUILT_INS)
	{
		if (ft_strcmp(list->tokens_in_node->cmd, built_in[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	exec_built_in(t_minishell *data, t_list *list)
{
	int		index;
	void	(*built_in_funcs[NUM_OF_BUILT_INS])(t_minishell *, char **);

	built_in_funcs[0] = &ft_pwd;
	built_in_funcs[1] = &ft_echo;
	built_in_funcs[2] = &ft_exit;
	index = is_built_in(list);
	if (index == -1)
		return ;
	built_in_funcs[index](data, list->tokens_in_node->args);
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

void	exec_simple_cmd(t_exec *exec, t_list *list, t_minishell *data,
		char *path)
{
	pid_t	pid;
	int		status;
	char	**env;

	if (is_built_in(list) != -1)
		return (exec_built_in(data, list));
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		// rentre pas ici
		// redir_exec(list);

		// ICI !!!
		printf("hi");
		env = create_char_env(data->env);
		if (!env)
			free_minishell(data);
		// printf("%s", (char *)env);
		if (execve(path, exec->av, env) == -1)
			perror("execve");
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
	// 	if (WIFEXITED(status))
	// 		printf("Child exited with status %d\n", WEXITSTATUS(status));
	// 	else if (WIFSIGNALED(status))
	// 		printf("Child was killed by signal %d\n", WTERMSIG(status));
	}
}

void	exec(t_list *list, t_minishell *data)
{
	t_exec	exec_struct;
	int		i;
	char *path;

	path = NULL;
	exec_struct.av = NULL;
	convert_to_exec_args(list, &exec_struct);
	if (exec_struct.av != NULL)
	{
		if (is_built_in(list) == -1)
			path = get_cmd_path(list->tokens_in_node->cmd, data);
		exec_simple_cmd(&exec_struct, list, data, path);
		// else
		// 	printf("Command not found: %s\n", list->tokens_in_node->cmd);
		i = 0;
		while (exec_struct.av[i] != NULL)
			free(exec_struct.av[i++]);
		free(exec_struct.av);
	}
}
