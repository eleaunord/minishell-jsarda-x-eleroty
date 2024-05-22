/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_execve_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:07:08 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/22 16:00:15 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	convert_to_exec_args(t_list *list, t_exec *exec_struct)
{
	int		arg_count;
	int		i;
	int		j;
	t_exec	*exec_struc;

	arg_count = ft_strlen(list->args);
	i = -1;
	j = 0;
	exec_struct->av = malloc(sizeof(char *) * (arg_count + 2));
	if (!exec_struc->av)
		return (perror("malloc"));
	exec_struc->av[0] = ft_strdup(list->cmd);
	if (!exec_struct->av[0])
		return (perror("strdup"), free(exec_struct->av));
	while (++i < arg_count)
	{
		exec_struct->av[i + 1] = ft_strdup(list->args[i]);
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
