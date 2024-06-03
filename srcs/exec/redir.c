/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:40:39 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/03 12:48:38 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_in(t_token redir)
{
	int	fd;

	fd = open(redir.file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting stdin");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redir_out(t_token redir)
{
	fd = open(redir.file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting stdout");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	appen_redir_out(t_token redir)
{
	fd = open(redir.file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting stdout");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redir(t_token redir)
{
	int	fd;

	if (redir.type == REDIR_IN_TOKEN)
		redir_in(redir);
	else if (redir.type == REDIR_OUT_TOKEN)
		redir_out(redir);
	else if (redir.type == APPEND_TOKEN)
		appen_redir_out(redir);
	// Note: HEREDOC_REDIR is not handled in this function.
}
