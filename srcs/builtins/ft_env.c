/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:00:11 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/04 12:24:44 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_minishell *data, char **args)
{
	t_env	*start;

	(void)args;
	start = data->env;
	if (!data->env)
		return ; // need to add pwd , shlvl , _
	ft_putendl_fd(data->env->str, 1);
	data->env = data->env->next;
	while (data->env != start)
	{
		ft_putendl_fd(data->env->str, 1);
		data->env = data->env->next;
	}
}
