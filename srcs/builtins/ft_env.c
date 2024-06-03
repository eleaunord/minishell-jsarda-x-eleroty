/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:00:11 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/03 10:31:14 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_env(t_minishell *data, char **args)
{
	(void)args;

	while (data->env)
	{
		ft_putendl_fd(data->env->value, 1);
		data->env = data->env->next;
	}
	if (data->env)
		ft_putendl_fd(data->env->value, 1);
	return ;
}
