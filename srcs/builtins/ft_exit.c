/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:30 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/20 11:06:29 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exit(t_minishell *data, int value, int status_value)
{
	data->exit = value;
	data->exit_status = status_value;
}

void	ft_exit(t_minishell *data, t_node *node, char **args)
{
	int	args_count;

	(void)node;
	args_count = count_args(args);
	if (args_count > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
		return ;
	}
	else if (args_count == 2)
	{
		if (!ft_isdigit(args[1]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			set_exit(data, 1, 2);
			return ;
		}
		ft_putstr_fd("exit\n", 1);
		set_exit(data, 1, atoi(args[1]));
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	set_exit(data, 1, 0);
	return ;
}
