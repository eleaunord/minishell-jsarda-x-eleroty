/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:14:37 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 12:23:57 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_builtins(t_node *data, t_minishell *shell, char *eof, char *file_name)
{
	if (!eof)
		return (free(data->last_heredoc), 1);
	data->fdin = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fdin == -1)
		return (free(data->last_heredoc), 1);
	data->pid = fork();
	if (data->pid == 0)
	{
		manage_sig();
		readline_loop(eof, data->fdin);
		close(data->fdin);
		return (1);
	}
	else
		wait(NULL);
	if (ft_lstsize_cmd(shell->nodes) == 1)
		close(data->fdin);
	return (0);
}

int	redir_in_builtins(t_node *data, char *file_name)
{
	data->fdin = open(file_name, O_RDONLY, 0644);
	if (data->fdin == -1)
		return (1);
	if (is_built_in(data) == -1 && dup2(data->fdin, STDIN_FILENO) == -1)
	{
		perror("Error redirecting stdin");
		return (1);
	}
	return (0);
}

int	redir_out_builtins(t_node *data, t_minishell *shell, char *file_name)
{
	data->fdout = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fdout == -1)
		return (1);
	if ((ft_lstsize_cmd(shell->nodes) > 1 || is_built_in(data) == -1)
		&& dup2(data->fdout, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting stdout");
		close(data->fdout);
		return (1);
	}
	return (0);
}

int	appen_redir_out_builtins(t_node *data, t_minishell *shell, char *file_name)
{
	data->fdout = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fdout == -1)
		return (1);
	if ((ft_lstsize_cmd(shell->nodes) > 1 || is_built_in(data) == -1)
		&& dup2(data->fdout, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting stdout");
		return (1);
	}
	return (0);
}

int	handle_redir_builtins(t_node *data, t_minishell *shell, int i)
{
	int	status;

	i = 0;
	if (data->is_here_doc == 1)
		status = redir_in_builtins(data, data->last_heredoc);
	while (data->filename_in && data->filename_in[i])
	{
		if (data->fdin != 0 && data->fdin != -1)
			close(data->fdin);
		if (data->is_redir_in == 1)
			status = redir_in_builtins(data, data->filename_in[i]);
		i++;
	}
	i = 0;
	while (data->filename_out && data->filename_out[i])
	{
		if (data->fdout != 1 && data->fdout != -1)
			close(data->fdout);
		if (data->is_redir_out == 1)
			status = redir_out_builtins(data, shell, data->filename_out[i]);
		else if (data->is_append == 1)
			status = appen_redir_out_builtins(data, shell, data->filename_out[i]);
		i++;
	}
	return (status);
}
