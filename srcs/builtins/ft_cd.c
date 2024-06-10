/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:01:41 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/10 10:26:11 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_minishell *data, t_node *node, char **args)
{
	(void)node;
	int	cd_ret;

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
