/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:09:00 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/04 14:18:22 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_list *list, t_minishell *data)
{
	t_exec	exec_struct;
	int		i;
	char	*path;

	int		nums_cmd;
	path = NULL;
	nums_cmd = 0;
	exec_struct.av = NULL;
	convert_to_exec_args(list, &exec_struct);
	if (exec_struct.av != NULL)
	{
		if (is_built_in(list) == -1)
			path = get_cmd_path(list->tokens_in_node->cmd, data);
		// if (size > 1)
		// {
		// 	nums_cmd = get_nums_cmd();
		// 	exec_pipeline(list->tokens_in_node->cmd, nums_cmd);
		// }
		// else
		exec_simple_cmd(&exec_struct, list, data, path);
		i = 0;
		while (exec_struct.av[i] != NULL)
			free(exec_struct.av[i++]);
		free(exec_struct.av);
	}
}


