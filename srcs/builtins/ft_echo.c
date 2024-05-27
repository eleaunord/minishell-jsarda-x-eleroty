/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:41:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/27 18:30:53 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	n_option;

	i = 0;
	n_option = 0;
	if (count_args(args) > 1)
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
// static int	check_new_line(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] && str[i] == '-')
// 	{
// 		++i;
// 		while (str[i] && str[i] == 'n')
// 			i++;
// 		if (i == (int)ft_strlen(str))
// 			return (1);
// 	}
// 	return (0);
// }

// static void	write_echo(int count, int i, bool new_line, char **args)
// {
// 	while (args[i] && check_new_line(args[i]))
// 	{
// 		++i;
// 		new_line = false;
// 	}
// 	while (i < count)
// 	{
// 		write(1, args[i], ft_strlen(args[i]));
// 		if (i != count - 1)
// 			write(1, " ", 1);
// 		++i;
// 	}
// 	if (new_line)
// 		write(1, "\n", 1);
// }

// void	ft_echo(char **args)
// {
// 	int		count;
// 	int		i;
// 	bool	new_line;

// 	count = 0;
// 	printf("%s", "eh");
// 	while (args[count])
// 	{
// 		printf("%s", args[count]);
// 		++count;
// 	}
// 	i = 1;
// 	new_line = true;
// 	write_echo(count, i, new_line, args);

// }