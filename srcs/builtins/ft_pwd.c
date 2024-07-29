/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:35:20 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 10:36:32 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_node *data, t_minishell *shell, char **args)
{
	char	cwd[PATH_MAX];

	(void)shell;
	(void)args;
	if (getcwd(cwd, PATH_MAX))
		ft_putendl_fd(cwd, data->fdout);
	else
	{
		perror("pwd");
		g_status = 1;
		return ;
	}
	g_status = 0;
}
