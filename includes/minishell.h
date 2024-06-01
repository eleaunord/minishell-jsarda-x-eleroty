#ifndef TOKENS_H
# define TOKENS_H

// Librairies
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
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

#define COLOR_RESET   "\x1b[0m"
#define COLOR_GREEN   "\x1b[32m"

# define INPUT 1   //"<"
# define HEREDOC 2 //"<<"
# define TRUNC 3   //">"
# define APPEND 4  //">>"
# define PIPE 5    //"|"
# define CMD 6
# define ARG 7
# define SINGLE_QUOTE 39
# define PATH_MAX 500
# define NUM_OF_BUILT_INS 4
// TOKEN LINKED LIST

/*

liste chainee de token pour chaque elements de la ligne de commande
-> str et int pour chaque maillon
-> str = WORD aka ce qui est visuel (cat,
		| ) ; int = token aka type de token (CMD, PIPE)

*/

// MINISHELL STRUCT
typedef enum e_token_type
{
	TOKEN_WORD,
	// "word" ; = 0 (bc first enumerator in our enum e_token_type)
	APPEND_TOKEN,    // ">>" ; = 1
	REDIR_OUT_TOKEN, // ">" ; = 2
	HEREDOC_TOKEN,   // "<<" ; = 3
	REDIR_IN_TOKEN,  // "<" ; = 4
}						t_token_type;

// typedef	struct			s_redir
// {
// 	char				*out1;
// 	char				*out2;
// 	char				*in;
// 	int					sstdout;
// 	int					sstderr;
// 	int					sstdin;
// 	int					end;
// 	int					i;
// 	char				*name;
// 	char				*value;
// }						t_redir;

// TOKENS INSIDE NODES
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	char				*cmd;
	char				**args;
	// REDIRECTIONS
	char *filename;
	int					sstdout;
	int processed;
}						t_token;

// NODES
// Env struct
typedef struct s_env
{
	char				*str;
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_list
{
	struct s_list		*next;
	struct s_list		*prev;
	void				*content;
	struct s_token		*tokens_in_node;
}						t_list;

// Struct qui centralise tout
typedef struct s_minishell
{
	t_env				*env;
	t_list				*nodes;
	// a completer au fur et a mesure
	int					exit;
	int					exit_status;
}						t_minishell;

typedef struct s_exec
{
	char				**av;
	char				*path;
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
void					exec(t_list *list, t_minishell *data);
char					*get_cmd_path(char *cmd, t_minishell *data);
char					*get_path_value(t_minishell *data, char *key);
char					**create_char_env(t_env *env);
// BUILTINS
void	ft_exit(t_minishell *data, char **args);
void					ft_pwd(t_minishell *data, char **args);
void					ft_echo(t_minishell *data, char **args);
void				ft_cd(t_minishell *data, char **args);

// PARSING FUNCTIONS
int						init_env(t_minishell *data, char **env);
int						open_quote_check(char *line);
t_token					*tokenize_input(char *line);
void					parse_tokens(t_token *tokens);
int						is_space(char *line);
int						is_separator(char *c);
char					*create_token(char *str, int start, int end);
void					ft_split_operators(t_list *token_list);
void					insert_node(t_list *elem, t_list *new_elem);
t_list					*ft_split_list(char *line, t_list *minishell,
							t_command **command);
char					*create_token(char *str, int start, int end);
char					*process_in_quotes(char *line, t_position_tracker *p,
							t_command **cmd, t_list *mini);
char	*ft_split_pipes_spaces(char *line, t_list **tokens_list);
char					*remove_quotes(char *line);
int						ft_strcmp(char *s1, char *s2);
int						main(int argc, char *argv[], char *env[]);
int						tokenizer(char *line, t_list **nodes,
							t_minishell *mini);
void					free_env(char ***envp);
void					free_minishell(t_minishell *mini);
void					free_env_list(t_env *env_list);
int						init_env(t_minishell *mini, char **env_array);
void					print_env(t_env *list);
void					expander(t_token *token, t_minishell *mini);
int						check_env_var(char *token);
void					extract_substring(char *token, int start, int end,
							char **final_str);
char					*is_envar_expansible(char *token, int *i,
							char **final_str, t_minishell *mini);
int						is_alpha_underscore(int c);
void					*ft_memcpy(void *dest, const void *src, size_t n);
char					*ft_itoa(int n);
int						is_brace_expansion(char *token, int *i,
							char **final_str);
void					proceed_expansion(char *token, int *i, char **final_str,
							t_minishell *mini);
void					ft_putstr_fd(char *s, int fd);
int	special_tokens(char *input, t_token **tokens, int index);
t_token					*new_token(t_token_type type, char *value);
int word_token(char *input, t_token **tokens, int index);
void					add_token_to_list(t_token **tokens, t_token *new_token);
void	process_redirection(t_token **tokens);
// LIBFT FUNCTIONS
char					**ft_split(char const *s, char c);
void					free_split(char **split);
void					ft_putstr_fd(char *s, int fd);
char					*ft_strndup(const char *s, size_t n);
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
size_t					count_args(char **args);
char					*ft_strchr(const char *s, int c);
int	ft_isdigit(char *c);

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
