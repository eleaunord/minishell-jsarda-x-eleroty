/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:35:20 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/10 10:15:23 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_minishell *data, t_node *node, char **args)
{
	char cwd[PATH_MAX];

	(void)args;
	(void)data;
	(void)node;
	if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
	else
		perror("pwd");
}
