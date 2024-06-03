/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:18:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/03 15:24:28 by jsarda           ###   ########.fr       */
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
	built_in[3] = "cd";
	built_in[4] = "env";
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
	index = is_built_in(list);
	if (index == -1)
		return ;
	built_in_funcs[index](data, list->tokens_in_node->args);
}

int	check_if_redir(char *cmd)
{
	if (ft_strcmp(cmd, ">") == 0)
		return (0);
	if (ft_strcmp(cmd, "<") == 0)
		return (0);
	if (ft_strcmp(cmd, "<<") == 0)
		return (0);
	if (ft_strcmp(cmd, ">>") == 0)
		return (0);
	return (1);
}

void	exec_simple_cmd(t_exec *exec, t_list *list, t_minishell *data,
		char *path)
{
	pid_t	pid;
	int		status;
	char	**env;
	t_token	*current;

	if (is_built_in(list) != -1)
		return (exec_built_in(data, list));
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		current = list->tokens_in_node;
		while (current)
		{
			handle_redir(current);
			current = current->next;
		}
		env = create_char_env(data->env);
		if (!env)
		{
			free_minishell(data);
			exit(EXIT_FAILURE);
		}
		if (list->tokens_in_node->cmd
			&& check_if_redir(list->tokens_in_node->cmd) != 0)
			if (execve(path, exec->av, env) == -1)
				perror("execve");
		exit(0); // free all
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
	}
}
