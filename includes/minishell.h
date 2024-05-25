#ifndef TOKENS_H
# define TOKENS_H

// Librairies
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// TOKEN LIST

/*

Règles de Tokenisation :

	Redirections :
		< devient le token INPUT (1).
		> devient le token TRUNC (3).
		<< devient le token HEREDOC (2).
		>> devient le token APPEND (4).

	Premier Token :
		Le premier token d'une ligne de commande est CMD (6),
			sauf s'il s'agit d'une redirection.

	Arguments :
		Tous les tokens suivants un CMD ou une redirection (INPUT, TRUNC,
			HEREDOC, APPEND) sont des ARG (7).

	Pipes :
		| devient le token PIPE (5).
		Après un PIPE, le prochain token est soit une redirection, soit un CMD.

*/

# define INPUT 1   //"<"
# define HEREDOC 2 //"<<"
# define TRUNC 3   //">"
# define APPEND 4  //">>"
# define PIPE 5    //"|"
# define CMD 6
# define ARG 7
# define SINGLE_QUOTE 39
# define PATH_MAX 500
// TOKEN LINKED LIST

/*

liste chainee de token pour chaque elements de la ligne de commande
-> str et int pour chaque maillon
-> str = WORD aka ce qui est visuel (cat,
		| ) ; int = token aka type de token (CMD, PIPE)

*/

// MINISHELL STRUCT

// List chainee de maillons
typedef struct s_list
{
	// Each links have :
	char				*cmd;
	char				**args;
	char				*redrinIn;
	int					fdredirIn;
	char				*redrinOut;
	int					fdredirOut;
	// Next and prev links
	struct s_list		*next;
	struct s_list		*prev;
	// For libft functions
	void				*content;
}						t_list;

// Env struct
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;


// Struct qui centralise tout
typedef struct s_minishell
{
	t_env				*env;
	t_list				*nodes;
	// a completer au fur et a mesure

}						t_minishell;

typedef struct s_exec
{
	char				**av;
}						t_exec;

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
void					perror_handler(char *type);
void					convert_to_exec_args(t_list *list, t_exec *exec_struct);

// PARSING FUNCTIONS
int						is_space(const char num);
int						is_separator(char *c);
char					*create_token(char *str, int start, int end);
void					ft_split_operators(t_list *token_list);
void					insert_node(t_list *elem, t_list *new_elem);
t_list					*ft_split_list(char *line, t_list *minishell,
							t_command **command);
char					*create_token(char *str, int start, int end);
char					*process_in_quotes(char *line, t_position_tracker *p,
							t_command **cmd, t_list *mini);
void					ft_split_pipes_spaces(char *line, t_list **tokens_list);
char					*remove_quotes(char *line);
int						main(int argc, char *argv[]);
int						tokenizer(char *line, t_list *tokens_list);
void					free_env(char ***envp);
void					free_minishell(t_minishell *mini);
void					free_env_list(t_env *env_list);
int						init_env(t_minishell *mini, char **env_array);
// LIBFT FUNCTIONS
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_putendl_fd(char const *s, int fd);
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstadd_back(t_list **lst, t_list *new);
t_list					*ft_lstnew(void *content);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *s);
void					*ft_calloc(size_t nmemb, size_t size);
void					*ft_bzero(void *s, size_t bytes);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					*ft_bzero(void *s, size_t bytes);
char					*ft_strdup(const char *s);
int						ft_lstsize(t_list *lst);

// USEFUL FUNCTIONS FOR DEBUG
void					print_list(t_list *head);

// DRAFT

// typedef struct s_list
// {
// 	void				*content;
// 	int					type;
// 	struct s_list		*next;
// 	struct s_list		*prev;
// 	int					loop;
// }						t_list;

#endif
