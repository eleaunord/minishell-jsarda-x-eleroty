/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:30 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/26 10:05:43 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_minishell *data, t_node *node, char **args)
{
	(void)node;
	if (count_args(args) > 2)
	{
		data->exit = 1;
		return (ft_error("exit\nminishell: exit: too many arguments", NULL, 2,
				data));
	}
	else if (count_args(args) == 2)
	{
		if (!ft_isdigit(args[1]))
		{
			data->exit = 1;
			return (ft_error("exit\nminishell: exit: numeric argument required",
					NULL, 2, data));
		}
		data->exit = 1;
		data->exit_status = atoi(args[1]);
		return (ft_putstr_fd("exit\n", 1));
	}
	data->exit = 1;
	data->exit_status = 0;
	return (ft_putstr_fd("exit\n", 1));
}
