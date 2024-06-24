/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:41:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/20 10:54:59 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i = 1;
		while (str[i] == 'n')
			i++;
	}
	if (str[i])
		return (-1);
	return (1);
}

void	ft_echo(t_minishell *data, t_node *node, char **args)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	(void)data;
	(void)node;
	while (args[i] && check_arg(args[i]) == 1)
	{
		n_option = 1;
		i++;
	}
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
}
