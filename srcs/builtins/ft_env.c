/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:00:11 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/10 10:33:11 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_minishell *data, t_node *node, char **args)
{
	t_env	*start;

	(void)args;
	(void)node;
	start = data->env;
	if (!data->env)
		return ; // need to add pwd , shlvl , _
	print_env(data->env);
}
