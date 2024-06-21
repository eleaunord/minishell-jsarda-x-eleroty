/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:01:41 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/20 10:54:03 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_minishell *data, t_node *node, char **args)
{
	int	cd_ret;

	(void)node;
	if (!args[1])
		cd_ret = chdir(get_path_value(data, "HOME"));
	else
	{
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			perror("minishell: cd:");
	}
}
