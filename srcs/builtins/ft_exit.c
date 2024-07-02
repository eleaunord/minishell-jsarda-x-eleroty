/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:30 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/01 10:43:07 by jsarda           ###   ########.fr       */
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

int	ft_check_arg(char *s)
{
	int						i;
	unsigned long long int	nb;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (s[0] == '-')
		nb = ft_atol(s + 1);
	else
		nb = ft_atol(s);
	if (nb > LONG_MAX)
		return (0);
	return (1);
}

void	ft_exit(t_minishell *data, t_node *node, char **args)
{
	long long	nb;

	(void)node;
	if (count_args(args) > 1)
	{
		if (!ft_isdigit_str(args[1]))
		{
			data->exit_status = 2;
			print_exit_message(": numeric argument required", args[1], data);
		}
		else
		{
			if (!ft_check_arg(args[1]))
			{
				data->exit_status = 2;
				print_exit_message(": numeric argument required", args[1],
					data);
			}
			else
			{
				nb = ft_atol(args[1]);
				data->exit_status = nb;
				if (data->print_exit == 0)
					printf("exit\n");
			}
		}
		if (count_args(args) > 2)
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
	exit(data->exit_status);
}
