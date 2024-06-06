/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:30 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/06 15:23:03 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_minishell *data, char **args)
{
	int args_count;

	args_count = count_args(args);
	if (args_count > 1)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
		return ;
	}
	else if (args_count == 1)
	{
		if (!ft_isdigit(args[0]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 1);
			ft_putstr_fd(args[0], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			data->exit = 1;
			data->exit_status = 2;
			return ;
		}
		ft_putstr_fd("exit\n", 1);
		data->exit = 1;
		data->exit_status = atoi(args[0]);
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	data->exit = 1;
	data->exit_status = 0;
	return ;
}
