/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:30 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/28 14:27:59 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_exit_message(char *message, char *args, t_minishell *data)
{
	if (data->print_exit == 0)
		printf("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	if (args)
		ft_putstr_fd(args, 2);
	ft_putendl_fd(message, 2);
}

void	ft_exit(t_minishell *data, t_node *node, char **args)
{
	(void)node;
	if (count_args(args) > 1)
	{
		if (!ft_isdigit(args[1]))
		{
			data->exit_status = 2;
			print_exit_message(": numeric argument required", args[1], data);
		}
		else if (count_args(args) == 2 && count_args(args) < 3)
		{
			data->exit_status = ft_atol(args[1]);
			if (data->print_exit == 0)
				printf("exit\n");
		}
		else if (count_args(args) > 2)
		{
			data->exit_status = 1;
			print_exit_message(": too many arguments", NULL, data);
			return ;
		}
	}
	else
	{
		data->exit_status = 0;
		if (data->print_exit == 0)
			printf("exit\n");
	}
	free_minishell(data, node);
	return (exit(data->exit_status));
}
