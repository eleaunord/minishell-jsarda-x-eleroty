/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:46:17 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 10:33:28 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_node *data, t_minishell *shell, char **args)
{
	(void)args;
	if (!shell->env)
		return ;
	print_env(shell->env, data);
	g_status = 0;
}
