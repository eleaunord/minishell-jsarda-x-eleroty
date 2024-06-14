/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:18:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/14 11:59:20 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_built_in(t_node *list)
{
	int		i;
	char	*built_in[NUM_OF_BUILT_INS];

	if (!list->cmd)
		return (-1);
	built_in[0] = "pwd";
	built_in[1] = "echo";
	built_in[2] = "exit";
	built_in[3] = "cd";
	built_in[4] = "env";
	built_in[5] = "unset";
	built_in[6] = "export";
	i = 0;
	while (i < NUM_OF_BUILT_INS)
	{
		if (ft_strcmp(list->cmd, built_in[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	exec_built_in(t_minishell *data, t_node *list)
{
	int		index;
	void	(*built_in_funcs[NUM_OF_BUILT_INS])(t_minishell *, t_node *,
			char **);

	built_in_funcs[0] = &ft_pwd;
	built_in_funcs[1] = &ft_echo;
	built_in_funcs[2] = &ft_exit;
	built_in_funcs[3] = &ft_cd;
	built_in_funcs[4] = &ft_env;
	built_in_funcs[5] = &ft_unset;
	built_in_funcs[6] = &ft_export;
	index = is_built_in(list);
	if (index == -1)
		return ;
	built_in_funcs[index](data, list, list->args);
}

int	check_if_redir(t_node *node)
{
	if (node->tokens_in_node->type >= 1 && node->tokens_in_node->type <= 4)
		return (0);
	return (1);
}

void	exec_child_process(t_minishell *data, t_node *list, char *path)
{
	t_node	*current;
	char	**env;
	// int		i;
	// int		j;

	current = list;
	// i = data->command_count;
	// j = 0;
	// while (j < data->command_count - 1)
	// {
	// 	if (j != i - 1)
	// 	{
	// 		close(data->pipes[j][0]);
	// 	}
	// 	if (j != i)
	// 	{
	// 		close(data->pipes[j][1]);
	// 	}
	// 	j++;
	// 	i--;
	// }
	if (current->fd_in != STDIN_FILENO)
	{
		if (dup2(current->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(current->fd_in);
	}
	if (current->fd_out != STDOUT_FILENO)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(current->fd_out);
	}
	if (check_if_redir(current) == 0 || list->here_doc == 1)
		while (current)
		{
			handle_redir(current);
			current = current->next;
		}
	env = create_char_env(data->env);
	if (!env)
	{
		printf("no env\n");
		free_minishell(data, list);
		exit(EXIT_FAILURE);
	}
	if (list->cmd)
	{
		if (execve(path, list->args, env) == -1)
		{
			perror("execve");
			fprintf(stderr, "minishell: %s: command not found\n",
				list->tokens_in_node->cmd);
		}
	}
	free_minishell(data, list);
	exit(0);
}

void	exec_parent_process(pid_t pid)
{
	int	status;
	int i;

	i = 0;
	while (i < data->)
	// {
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
	// }
}

void	exec_cmd(t_minishell *data, t_node *list, char *path)
{
	pid_t	pid;

	if (is_built_in(list) != -1)
	{
		exec_built_in(data, list);
		return ;
	}
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
		exec_child_process(data, list, path);
	if (!data->pipes)
		exec_parent_process(pid);
}
