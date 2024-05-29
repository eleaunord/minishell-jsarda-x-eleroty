/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:41:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/28 15:06:52 by jsarda           ###   ########.fr       */
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

void	ft_echo(char **args)
{
	int	i;
	int	n_option;

	i = 0;
	n_option = 0;
	while (check_arg(args[i]) == 1)
	{
		n_option = 1;
		i++;
	}
	if (count_args(args) >= 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
}
