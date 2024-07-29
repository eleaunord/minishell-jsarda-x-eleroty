/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:14:37 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:41:28 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_builtins(t_node *data, t_shell *shell, char *eof, char *file_name)
{
	if (!eof)
		return (free(data->tmpfile_hd), 1);
	data->fdin = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fdin == -1)
		return (free(data->tmpfile_hd), 1);
	data->pid = fork();
	if (data->pid == 0)
	{
		manage_sig();
		readline_loop(data, shell, eof, data->fdin);
		close(data->fdin);
		return (1);
	}
	else
		wait(NULL);
	if (ft_lstsize_cmd(shell->datas) == 1)
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

int	redir_out_builtins(t_node *data, t_shell *shell, char *file_name)
{
	data->fdout = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fdout == -1)
		return (1);
	if ((ft_lstsize_cmd(shell->datas) > 1 || is_built_in(data) == -1)
		&& dup2(data->fdout, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting stdout");
		close(data->fdout);
		return (1);
	}
	return (0);
}

int	appen_redir_out_builtins(t_node *data, t_shell *shell, char *file_name)
{
	data->fdout = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fdout == -1)
		return (1);
	if ((ft_lstsize_cmd(shell->datas) > 1 || is_built_in(data) == -1)
		&& dup2(data->fdout, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting stdout");
		return (1);
	}
	return (0);
}

int	handle_redir_builtins(t_node *data, t_shell *shell, int i)
{
	int	status;

	i = 0;
	if (data->redir_type_in == HD)
		status = redir_in_builtins(data, data->tmpfile_hd);
	while (data->namein && data->namein[i])
	{
		if (data->fdin != 0 && data->fdin != -1)
			close(data->fdin);
		if (data->redir_type_in == IN)
			status = redir_in_builtins(data, data->namein[i]);
		i++;
	}
	i = 0;
	while (data->nameout && data->nameout[i])
	{
		if (data->fdout != 1 && data->fdout != -1)
			close(data->fdout);
		if (data->redir_type_out == OUT)
			status = redir_out_builtins(data, shell, data->nameout[i]);
		else if (data->redir_type_out == APPEND)
			status = appen_redir_out_builtins(data, shell, data->nameout[i]);
		i++;
	}
	return (status);
}
