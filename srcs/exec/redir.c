/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:36:05 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 16:19:14 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_node *data, t_minishell *shell, char *eof, char *file_name)
{
	if (!eof)
		return (ft_errors_exec(0, "syntax error near unexpected \
		token `newline'\n", NULL, 2), free(data->last_heredoc));
	data->fdin = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fdin == -1)
		return (ft_errors_exec(1, strerror(errno),
				NULL, errno), free(data->last_heredoc));
	data->pid = fork();
	if (data->pid == 0)
	{
		manage_sig();
		readline_loop(eof, data->fdin);
		close(data->fdin);
		free_child(data, shell, 0);
	}
	else
		ft_wait_hd(data);
	if (ft_lstsize_cmd(shell->nodes) == 1)
		close(data->fdin);
}

void	redir_in(t_node *data, t_minishell *shell, char *file_name)
{
	if (data->is_here_doc && !file_name)
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

void	handle_redir(t_minishell *shell, t_node *data)
{
	int	i;

	i = 0;
	if (data->is_here_doc == 1)
		redir_in(data, shell, data->last_heredoc);
	while (data->filename_in && data->filename_in[i])
	{
		if (data->fdin != 0 && data->fdin != -1)
			close(data->fdin);
		if (data->is_redir_in == 1)
			redir_in(data, shell, data->filename_in[i]);
		i++;
	}
	i = 0;
	while (data->filename_out && data->filename_out[i])
	{
		if (data->fdout != 1 && data->fdout != -1)
			close(data->fdout);
		if (data->is_redir_out == 1)
			redir_out(data, data->filename_out[i]);
		else if (data->is_append == 1)
			appen_redir_out(data, data->filename_out[i]);
		i++;
	}
}
