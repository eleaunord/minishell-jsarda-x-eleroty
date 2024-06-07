/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:40:39 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/07 12:04:24 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_in(t_token *redir)
{
	int	fd;

	// printf("in%s\n", redir->filename);
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

void	redir_in_heredoc(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
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
		close(fd);
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
	return (strdup(template));
}

// void	heredoc(char **eof, t_token *redir)
// {
// 	char	*buf;
// 	int		fd;
// 	char	*file;
// 	int		i;

// 	i = 0;
// 	(void)redir;
// 	buf = NULL;
// 	while (eof[i] != NULL)
// 	{
// 		file = get_tmp_file();
// 		if (!eof[i])
// 		{
// 			ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
// 				2);
// 			continue ;
// 		}
// 		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 		{
// 			perror("Error opening output file");
// 			exit(EXIT_FAILURE);
// 		}
// 		while (1)
// 		{
// 			buf = readline("> ");
// 			if (!ft_strncmp(eof, buf, INT_MAX))
// 				break ;
// 			ft_putendl_fd(buf, fd);
// 			free(buf);
// 		}
// 		close(fd);
// 		redir_in_heredoc(file);
// 		unlink(file);
// 		free(buf);
// 	}
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
	// 	heredoc(redir->limitators, redir);
}
