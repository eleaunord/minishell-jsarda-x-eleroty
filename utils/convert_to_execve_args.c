/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_execve_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:07:08 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/07 14:44:42 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_exec_struc(t_exec *exec_struc)
{
	exec_struc->av = NULL;
	exec_struc->path = NULL;
}

void	convert_to_exec_args(t_list *list, t_exec *exec_struct)
{
	int	arg_count;
	int	i;
	int	j;
	init_exec_struc(exec_struct);
	if (!list->tokens_in_node->cmd && list->tokens_in_node->args)
		return ;
	arg_count = count_args(list->tokens_in_node->args);
	i = -1;
	j = 0;
	exec_struct->av = malloc(sizeof(char *) * (arg_count + 2));
	if (!exec_struct->av)
		return (perror("malloc"));
	exec_struct->av[0] = ft_strdup(list->tokens_in_node->cmd);
	if (!exec_struct->av[0])
		return (perror("strdup"), free(exec_struct->av));
	while (++i < arg_count)
	{
		exec_struct->av[i + 1] = ft_strdup(list->tokens_in_node->args[i]); // SEGFAULT au strlen de ft_strdup
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
