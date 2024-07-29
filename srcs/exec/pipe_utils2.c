/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:42:21 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/25 13:56:08 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_sig(void)
{
	signal(SIGINT, handler_sig_cmd);
	signal(SIGQUIT, handler_sig_cmd);
	signal(SIGPIPE, handler_sig_cmd);
}

void	execve_fail(void)
{
	perror("execve");
	exit(EXIT_FAILURE);
}
