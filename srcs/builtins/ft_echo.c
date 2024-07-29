/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:46:02 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:40:47 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		if (str[i] == '\0')
			return (-1);
		while (str[i] == 'n')
			i++;
		if (str[i] != '\0')
			return (-1);
		return (1);
	}
	return (-1);
}

void	ft_echo(t_node *data, t_shell *shell, char **args)
{
	int	i;
	int	n_option;

	(void)data;
	(void)shell;
	i = 1;
	n_option = 0;
	while (args[i] && check_arg(args[i]) == 1)
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], data->fdout);
		if (args[i + 1])
			write(data->fdout, " ", 1);
		i++;
	}
	if (!n_option)
		write(data->fdout, "\n", 1);
	g_return_satus = 0;
}
