/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:54:23 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:40:52 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_message(char *message, char *args)
{
	printf("exit\n");
	fprintf(stderr, "minishell: exit: ");
	if (args)
		fprintf(stderr, "%s", args);
	fprintf(stderr, "%s\n", message);
}

int	ft_isdigit_str(const char *c)
{
	int	i;

	i = 0;
	if (c[0] == '-' || c[0] == '+')
		i++;
	while (c[i])
	{
		if (!isdigit(c[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_node *data, t_shell *shell, char **args)
{
	int						overflow;
	unsigned long long int	result;

	result = g_return_satus;
	if (count_args(data->args) > 1 && ft_isdigit_str(args[1]) == 1)
	{
		print_exit_message(": numeric argument required", args[1]);
		return (free_child(data, shell, 2));
	}
	if (count_args(data->args) > 2)
	{
		g_return_satus = 1;
		return (print_exit_message(" too many arguments", NULL));
	}
	if (args[1])
	{
		result = ft_atoll(args[1], &overflow);
		if (overflow)
		{
			print_exit_message(": numeric argument required", args[1]);
			return (free_child(data, shell, 2));
		}
	}
	printf("exit\n");
	free_child(data, shell, (int)result);
}
