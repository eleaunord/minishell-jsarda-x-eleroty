/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:36:05 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:41:33 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_node *data, t_shell *shell, char *eof, char *file_name)
{
	if (!eof)
		return (ft_errors_exec(0, "syntax error near unexpected \
		token `newline'\n", NULL, 2), free(data->tmpfile_hd));
	data->fdin = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fdin == -1)
		return (ft_errors_exec(1, strerror(errno),
				NULL, errno), free(data->tmpfile_hd));
	data->pid = fork();
	if (data->pid == 0)
	{
		manage_sig();
		readline_loop(data, shell, eof, data->fdin);
		close(data->fdin);
		free_child(data, shell, 0);
	}
	else
		ft_wait_hd(data);
	if (ft_lstsize_cmd(shell->datas) == 1)
		close(data->fdin);
}

void	redir_in(t_node *data, t_shell *shell, char *file_name)
{
	if (data->is_hd && !file_name)
		free_child(data, shell, 0);
	data->fdin = open(file_name, O_RDONLY, 0644);
}

void	redir_out(t_node *data, char *file_name)
{
	data->fdout = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	appen_redir_out(t_node *data, char *file_name)
{
	data->fdout = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	handle_redir(t_shell *shell, t_node *data)
{
	int	i;

	i = 0;
	if (data->redir_type_in == HD)
		redir_in(data, shell, data->tmpfile_hd);
	while (data->namein && data->namein[i])
	{
		if (data->fdin != 0 && data->fdin != -1)
			close(data->fdin);
		if (data->redir_type_in == IN)
			redir_in(data, shell, data->namein[i]);
		i++;
	}
	i = 0;
	while (data->nameout && data->nameout[i])
	{
		if (data->fdout != 1 && data->fdout != -1)
			close(data->fdout);
		if (data->redir_type_out == OUT)
			redir_out(data, data->nameout[i]);
		else if (data->redir_type_out == APPEND)
			appen_redir_out(data, data->nameout[i]);
		i++;
	}
}
