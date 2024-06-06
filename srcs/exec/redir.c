/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:40:39 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/05 16:38:36 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_in(t_token *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
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

void	redir_out(t_token *redir)
{
	int	fd;
	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	appen_redir_out(t_token *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

// void	heredoc(char *eof, t_token *redir)
// {
// 	char	*buf;
// 	int		fd;
// 	(void)redir;
// 	buf = NULL;
// 	if (!eof)
// 	{
// 		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
// 			2);
// 		return ;
// 	}
// 	fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Error opening output file");
// 		exit(EXIT_FAILURE);
// 	}
// 	while (1)
// 	{
// 		buf = readline("> ");
// 		if (!ft_strncmp(eof, buf, INT_MAX))
// 			break ;
// 		ft_putendl_fd(buf ,fd);
// 		free(buf);
// 	}
// 	close(fd);
// 	//redir_in(redir);
// 	free(buf);
// }

void	handle_redir(t_token *redir)
{
	if (redir->type == REDIR_IN_TOKEN)
		redir_in(redir);
	else if (redir->type == REDIR_OUT_TOKEN)
		redir_out(redir);
	else if (redir->type == APPEND_TOKEN)
		appen_redir_out(redir);
	// else if (redir->type == HEREDOC_TOKEN)
	// 	heredoc(redir->args[0], redir);
}
