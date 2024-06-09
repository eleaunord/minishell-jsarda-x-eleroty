#ifndef TOKENS_H
# define TOKENS_H

// Librairies
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>


# define NUM_OF_BUILT_INS 7

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

// TOKENS INSIDE NODES (only for parsing)
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	char				*cmd;
	char				**args;
	// REDIRECTIONS
	// char				*filename;
	int					processed;
	// EXPANSIONS
	char				*key_expansion;
}						t_token;

// Env struct
typedef struct s_env
{
	char				*str;
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

// NODES (from parsing to exec, with love)
typedef struct s_node
{
	// Making the nodes (for parsing)
	struct s_node		*next;
	struct s_node		*prev;
	void				*content;

	// Dealing with tokens (for parsing)
	struct s_token		*tokens_in_node;

	// From parsing to exec
	char				*cmd; // in arg[0]
	char				**args;
	int					arg_count;
	char *key_expansion; // in args

	// Redirections, filenames not in args
	char *filename_out; // >
	char *filename_in;  // <
	int					here_doc; // is there a here doc ? 1 : yes, 0 : no
	char				*limiter_hd; //eof
	
	// OTHER (?)
	// int fd_in; // <
	// int					fd_out;
}						t_node;

// Structure pour exec
typedef struct t_redir
{
	char				*filename;
	char				*eof;
	char				**heredoc;
	struct s_redir		*next;
	struct s_redir		*prev;
}						t_redir;

// // Struct qui centralise tout
typedef struct s_minishell
{
	t_env				*env;
	t_node				*nodes;
	// EXITS
	int					exit;
	int					exit_status;
	t_redir				redir;

}						t_minishell;

typedef struct s_exec
{
	char				**av;
	char				*path;
}						t_exec;


// EXEC FUNCTIONS
void					perror_handler(char *type);
void					convert_to_exec_args(t_node *list, t_exec *exec_struct);
void					exec(t_node *list, t_node *data);
char					*get_cmd_path(char *cmd, t_node *data);
char					*get_path_value(t_node *data, char *key);
char					**create_char_env(t_env *env);
void					exec_pipeline(char ***cmds, int num_cmds);
void					exec_simple_cmd(t_exec *exec, t_node *list,
							t_node *data, char *path);
int						is_built_in(t_node *list);
void					handle_redir(t_token *redir);
// BUILTINS
void					ft_exit(t_node *data, char **args);
void					ft_pwd(t_node *data, char **args);
void					ft_echo(t_node *data, char **args);
void					ft_cd(t_node *data, char **args);
void					ft_env(t_node *data, char **args);
void					ft_unset(t_node *data, char **args);
void					ft_export(t_node *data, char **args);
// PARSING FUNCTIONS
int						open_quote_check(char *line);
t_token					*tokenize_input(char *line);
int						is_space(char *line);
char					*create_token(char *str, int start, int end);
char					*create_token(char *str, int start, int end);
char					*ft_split_pipes_spaces(char *line,
							t_node **tokens_list);
char					*remove_quotes(char *line);
int						ft_strcmp(char *s1, char *s2);
int						tokenizer(char *line, t_node **nodes);
void					free_env(char ***envp);
void					free_minishell(t_minishell *mini);
void					free_env_list(t_env *env_list);
int	init_env(t_minishell *data, char **env);
void					print_env(t_env *list);
void					expander(t_token *token, t_node *mini);
void					free_tokens(t_token *tokens);
void					extract_substring(char *token, int start, int end,
							char **final_str);
char					*is_envar_expansible(char *token, int *i,
							char **final_str, t_node *mini);
int						is_alpha_underscore(int c);
void					*ft_memcpy(void *dest, const void *src, size_t n);
char					*ft_itoa(int n);
int						is_brace_expansion(char *token, int *i,
							char **final_str);
void					proceed_expansion(char *token, int *i, char **final_str,
							t_node *mini);
void					ft_putstr_fd(char *s, int fd);
int						special_tokens(char *input, t_token **tokens,
							int index);
t_token					*new_token(t_token_type type, char *value);
int						word_token(char *input, t_token **tokens, int index);
void					add_token_to_list(t_token **tokens, t_token *new_token);
void					parse_tokens(t_token *tokens, t_node *node);
void					call_expander(t_node *list, t_node *data);
char					*expand_variables(char *token);

char					*ft_strcpy(char *dest, const char *src);
void					close_quote_check(int *dq, int *sq, int *index, char c);
int						count_arguments(t_token *tokens);
void					free_nodes(t_node *list);
void					process_expansions(t_token **tokens, t_node *node);

// LIBFT FUNCTIONS
void					*ft_lstdelone(void *lst);
char					**ft_split(char const *s, char c);
void					free_split(char **split);
void					ft_putstr_fd(char *s, int fd);
char					*ft_strndup(const char *s, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_putendl_fd(char const *s, int fd);
void					ft_lstclear(t_node **lst, void (*del)(void *));
void					ft_lstadd_back(t_node **lst, t_node *new);
t_node					*ft_lstnew(void *content);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *s);
void					*ft_calloc(size_t nmemb, size_t size);
void					*ft_bzero(void *s, size_t bytes);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					*ft_bzero(void *s, size_t bytes);
char					*ft_strdup(const char *s);
int						ft_lstsize(t_node *lst);
size_t					count_args(char **args);
char					*ft_strchr(const char *s, int c);
int						ft_isdigit(char *c);
void					*ft_calloc(size_t count, size_t size);

// USEFUL FUNCTIONS FOR DEBUG
void					print_node(t_node *head);


#endif
