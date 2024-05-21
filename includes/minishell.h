/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:49:07 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/21 13:27:53 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

// DEFINE
# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7
# define IDENTIFIER 8
# define OPERATOR 9
# define L_PARENT 10
# define R_PARENT 10
# define STR 11
# define OPERATORS_STR "><|;"
# define SPACE_ 32
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

// MINISHELL STRUCTURES

/*

liste chainee de token pour chaque elements de la ligne de commande
-> str et int pour chaque maillon
-> str = WORD aka ce qui est visuel (cat,
		| ) ; int = token aka type de token (CMD, PIPE)

*/

typedef struct s_tokens
{
	void				*content;
	int					type;
	struct s_tokens		*next;
	struct s_tokens		*prev;
	int					loop;
}						t_tokens;

typedef struct s_command
{
	char				*token;
	int					length;
	int					type;
	struct s_command	*next;
}						t_command;

typedef struct s_position_tracker
{
	int					start;
	int					i;
}						t_position_tracker;

// EXEC FUNCTIONS
void	perror_handler(char *type);

// PARSING FUNCTIONS
int		is_space(const char num);
int		is_separator(char *c);
char	*create_token(char *str, int start, int end);
void	ft_split_operators(t_tokens *token_list);
void	insert_node(t_tokens *elem, t_tokens *new_elem);
t_tokens	*ft_split_tokens(char *line, t_tokens *minishell, t_command **command);
char	*create_token(char *str, int start, int end);
char	*process_in_quotes(char *line, t_position_tracker *p, t_command **cmd,
			t_tokens *mini);


// LIBFT FUNCTIONS
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putendl_fd(char const *s, int fd);
void	ft_lstclear(t_tokens **lst, void (*del)(void *));
void	ft_lstadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstnew(void *content, int type);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_bzero(void *s, size_t bytes);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_bzero(void *s, size_t bytes);
char	*ft_strdup(const char *s);
int		ft_lstsize(t_tokens *lst);

// USEFUL FUNCTIONS FOR DEBUG
void	print_tokens(t_tokens *head);
#endif
