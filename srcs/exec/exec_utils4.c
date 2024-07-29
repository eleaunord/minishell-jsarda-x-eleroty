/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:03:45 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/29 17:07:33 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dir_error(char *cmd)
{
	int	tmp;

	if (!cmd)
		return (0);
	tmp = open(cmd, O_DIRECTORY);
	if (tmp > 0)
	{
		ft_errors_exec(1, "Is a directory", cmd, 126);
		close(tmp);
		return (1);
	}
	if (tmp != -1)
		close(tmp);
	return (0);
}
