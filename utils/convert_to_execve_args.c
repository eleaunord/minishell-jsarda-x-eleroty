/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_execve_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:07:08 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/27 15:41:22 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	convert_to_exec_args(t_list *list, t_exec *exec_struct)
{
	int	arg_count;
	int	i;
	int	j;
	t_token *token;

	if (!list->tokens_in_node.args)
		return ;
	int x = 0;
	while (list != NULL)
	{
		token = (t_token *)list->content;
		while (token->args[x] != NULL)
		{
			printf("ARG[%d]: %s\n", x, token->args[x]); // OK
			x++;
		}
		list = list->next;
	}
	arg_count = x;
	printf("CMD %s\n", token->cmd); //OK
	printf("ARG COUNT = %d\n", arg_count); //OK
	// arg_count = count_args(list->tokens_in_node.args);
	i = -1;
	j = 0;
	exec_struct->av = malloc(sizeof(char *) * (arg_count + 2));
	if (!exec_struct->av)
		return (perror("malloc"));
	exec_struct->av[0] = ft_strdup(token->cmd);
	if (!exec_struct->av[0])
		return (perror("strdup"), free(exec_struct->av));
	while (++i < arg_count)
	{
		exec_struct->av[i + 1] = ft_strdup(token->args[i]);
		if (!exec_struct->av[i + 1])
		{
			perror("strdup");
			while (j <= i)
				free(exec_struct->av[j++]);
			return (free(exec_struct->av));
		}
	}
	exec_struct->av[arg_count + 1] = NULL;
}
