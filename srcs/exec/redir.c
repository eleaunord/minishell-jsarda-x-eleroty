/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:40:39 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/14 15:22:51 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_in(char *file_name_in)
{
	int	fd;

	fd = open(file_name_in, O_RDONLY);
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

void	redir_out(char *file_name_out)
{
	int	fd;

	fd = open(file_name_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting stdout");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	appen_redir_out(char *file_name_out)
{
	int	fd;

	fd = open(file_name_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

char	*get_tmp_file(void)
{
	char	template[] = "minishell-XXXXXX";
	int		random_fd;
	size_t	i;
	char	rand_char;

	i = 11;
	random_fd = open("/dev/urandom", O_RDONLY);
	if (random_fd == -1)
	{
		perror("Error opening /dev/urandom");
		exit(EXIT_FAILURE);
	}
	while (i < 22)
	{
		if (read(random_fd, &rand_char, 1) != 1)
		{
			perror("Error reading /dev/urandom");
			close(random_fd);
			exit(EXIT_FAILURE);
		}
		template[i] = 'a' + (rand_char % 26);
		i++;
	}
	template[i] = '\0';
	close(random_fd);
	return (ft_strdup(template));
}

void	heredoc(char *eof, char *file_name_in)
{
	char	*buf;
	int		fd;

	if (!eof)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		return ;
	}
	file_name_in = "testheredoc";
	fd = open(file_name_in, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		buf = readline("> ");
		if (buf && !ft_strncmp(eof, buf, INT_MAX) && eof)
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
	close(fd);
}

void	handle_redir(t_node *redir)
{
	int	i;

	i = 0;
	while (redir->filename_in[i] || redir->filename_out[i])
	{
		if (redir->tokens_in_node->type == HEREDOC_TOKEN)
		{
			redir_in(redir->filename_in[i]);
			unlink(redir->filename_in[i]);
		}
		else if (redir->tokens_in_node->type == REDIR_IN_TOKEN)
			redir_in(redir->filename_in[i]);
		else if (redir->tokens_in_node->type == REDIR_OUT_TOKEN)
			redir_out(redir->filename_out[i]);
		else if (redir->tokens_in_node->type == APPEND_TOKEN)
			appen_redir_out(redir->filename_out[i]);
		i++;
	}
}
