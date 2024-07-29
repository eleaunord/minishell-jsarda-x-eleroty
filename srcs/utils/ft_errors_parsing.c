/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:28:56 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/22 16:06:43 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_errors_parsing(int err, char *msg, t_shell *shell, char *supp)
{
	(void)shell;
	if (err == 0)
	{
		g_return_satus = 2;
		return (write(2, "minishell: ", 11), ft_putstr_fd(msg, 2));
	}
	if (err == 1)
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(supp, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(msg, 2);
		g_return_satus = 1;
		return ;
	}
}
