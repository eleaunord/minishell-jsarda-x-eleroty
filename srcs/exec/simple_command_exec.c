/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:18:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/03 13:51:21 by jsarda           ###   ########.fr       */
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
		// redir_exec(list);
		env = create_char_env(data->env);
		if (!env)
			free_minishell(data);
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
