/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:18:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/07 11:17:48 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_built_in(t_list *list)
{
	int		i;
	char	*built_in[NUM_OF_BUILT_INS];

	if (!list->tokens_in_node->cmd)
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
	built_in_funcs[3] = &ft_cd;
	built_in_funcs[4] = &ft_env;
	built_in_funcs[5] = &ft_unset;
	built_in_funcs[6] = &ft_export;
	index = is_built_in(list);
	if (index == -1)
		return ;
	built_in_funcs[index](data, list->tokens_in_node->args);
}

int	check_if_redir(t_token *token)
{
	if (token->type >= 1 && token->type <= 4)
		return (0);
	return (1);
}

void	exec_child_process(t_list *list, t_minishell *data, char *path,
		t_exec *exec)
{
	t_token	*current;
	char	**env;

	current = list->tokens_in_node;
	if (check_if_redir(current) == 0)
	{
		while (current)
		{
			handle_redir(current);
			current = current->next;
		}
	}
	env = create_char_env(data->env);
	if (!env)
	{
		free_minishell(data);
		exit(EXIT_FAILURE);
	}
	if (list->tokens_in_node->cmd)
	{
		if (execve(path, exec->av, env) == -1)
		{
			perror("execve");
			fprintf(stderr, "minishell: %s: command not found\n",
				list->tokens_in_node->cmd);
		}
	}
	free_minishell(data);
	exit(0);
}

void	exec_parent_process(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		perror("waitpid");
}

void	exec_simple_cmd(t_exec *exec, t_list *list, t_minishell *data,
		char *path)
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
		exec_child_process(list, data, path, exec);
	else
		exec_parent_process(pid);
}
