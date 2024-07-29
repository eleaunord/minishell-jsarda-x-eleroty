/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:43:07 by juliensarda       #+#    #+#             */
/*   Updated: 2024/07/22 09:23:00 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_error(int err_status, char *msg, char *supp)
{
	write(2, "minishell: ", 12);
	ft_putstr_fd(supp, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	g_return_satus = err_status;
}

void	export_error(int err_status, char *msg, char *supp)
{
	write(2, "export: ", 9);
	ft_putstr_fd(supp, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	g_return_satus = err_status;
}

void	ft_errors_exec(int err, char *msg, char *supp, int err_status)
{
	if (err == 0)
		return (write(2, "minishell: ", 12), ft_putstr_fd(msg, 2));
	if (err == 1)
		return (minishell_error(err_status, msg, supp));
	if (err == 2)
		return (export_error(err_status, msg, supp));
}
