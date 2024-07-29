/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:35:20 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:40:57 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_node *data, t_shell *shell, char **args)
{
	char	cwd[PATH_MAX];

	(void)shell;
	(void)data;
	(void)args;
	if (getcwd(cwd, PATH_MAX))
		ft_putendl_fd(cwd, data->fdout);
	else
	{
		perror("pwd");
		g_return_satus = 1;
		return ;
	}
	g_return_satus = 0;
}
