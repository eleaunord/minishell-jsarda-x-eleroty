/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:11:03 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/30 18:13:55 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_loop(t_node *tmp_data, int i, int fd)
{
	i = 0;
	while (tmp_data->filename_in && tmp_data->filename_in[i])
	{
		tmp_data->fdintmp = open(tmp_data->filename_in[i], O_RDONLY, 0644);
		if (tmp_data->fdintmp == -1)
			return (ft_errors_exec(1, strerror(errno),
					tmp_data->filename_in[i], 2), 2);
		close(tmp_data->fdintmp);
		i++;
	}
	i = 0;
	while (tmp_data->filename_out && tmp_data->filename_out[i])
	{
		fd = open(tmp_data->filename_out[i], O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (ft_errors_exec(1, strerror(errno),
					tmp_data->filename_out[i], 2), 2);
		close(fd);
		i++;
	}
	return (0);
}

int	open_files(t_node **datas)
{
	t_node	*tmp_data;

	tmp_data = *datas;
	while (tmp_data)
	{
		if (open_file_loop(tmp_data, 0, -1))
			return (2);
		tmp_data = tmp_data->next;
	}
	return (0);
}

void	ft_close(t_node *data)
{
	while (data)
	{
		if (data->fdin != -1 && data->fdin != 0)
			close(data->fdin);
		if (data->fdout != -1 && data->fdout != 1)
			close(data->fdout);
		data = data->next;
	}
}

int	exec(t_minishell *shell)
{
	t_node	*datas;
	int		nb_cmd;

	nb_cmd = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	datas = shell->nodes;
	handle_heredoc(shell, datas);
	open_files(&datas);
	datas = shell->nodes;
	if (datas->next != NULL)
	{
		nb_cmd = ft_lstsize_cmd(shell->nodes);
		exec_pipe(shell, nb_cmd);
	}
	else
		exec_simple_cmd(datas, shell);
	ft_close(datas);
	free_hd_file(&(shell->nodes), 2);
	free_hd_file(&(shell->nodes), 1);
	return (0);
}
