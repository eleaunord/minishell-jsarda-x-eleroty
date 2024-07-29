/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:12:43 by juliensarda       #+#    #+#             */
/*   Updated: 2024/07/29 12:15:14 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readline_loop(char *eof, int fd)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		if (buf && !ft_strcmp(eof, buf))
		{
			free(buf);
			break ;
		}
		if (buf)
		{
			ft_putendl_fd(buf, fd);
			free(buf);
		}
	}
}

void	ft_wait_hd(t_node *data)
{
	int	status;

	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status) + 128;
	g_status = status;
	if (g_status == 130)
		printf("\n");
}
