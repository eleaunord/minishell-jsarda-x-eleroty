/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:09:00 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/10 10:02:51 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_node *list, t_minishell *data)
{
	int		i;
	char	*path;
	int		nums_cmd;

	path = NULL;
	nums_cmd = 0;
	if (is_built_in(list) == -1 && list->cmd)
		path = get_cmd_path(list->cmd, data);
	// if (size > 1)
	// {
	// 	nums_cmd = get_nums_cmd();
	// 	exec_pipeline(list->tokens_in_node->cmd, nums_cmd);
	// }
	// else
	exec_simple_cmd(data, list, path);
	i = 0;
}
