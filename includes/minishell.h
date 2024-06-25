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
#include <stdarg.h>
#include <stddef.h>
#include <errno.h>

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
}					t_token_type;

// TOKENS INSIDE NODES (only for parsing)
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	char			*cmd;
	char			**args;
	// REDIRECTIONS
	// char				*filename;
	int				processed;
	// EXPANSIONS
	char			*key_expansion;
	int				limiter_hd_count;
}					t_token;

// Env struct
typedef struct s_env
{
	char			*str;
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

// NODES (from parsing to exec, with love)
typedef struct s_node
{
	// Making the nodes (for parsing)
	struct s_node	*next;
	struct s_node	*prev;
	void			*content;

	// Dealing with tokens (for parsing)
	struct s_token	*tokens_in_node;

	// From parsing to exec
	char *cmd; // in arg[0]
	int				cmd_count;
	char			**args;
	int				arg_count;
	char **key_expansion; // in args
	int				expansion_count;
	int lonely_expansion;
		// Redirections, filenames not in args
		// NEW STRUCTURE FOR FILENAMES :
		int file_count;
	char			**filenames;
	char			heredoc_filename[36];
	int redir; // is there a redir ? 1 : yes, 0 : no

	// OLD STRUCTURE FOR FILENAMES :
	// char *filename_out; // >
	// char *filename_in;  // <
	char			**filename_in;
	char			**filename_out;
	int				file_in_count;
	int				file_out_count;
	int redir_in;      // is there a redir in ? 1 : yes, 0 : no
	int redir_out;     // is there a redir out ? 1 : yes, 0 : no
	int here_doc;      // is there a here doc ? 1 : yes, 0 : no
	char **limiter_hd; // eof
	int				limiter_hd_count;
	char			*last_heredoc;
	int				pipes[2];
	int error_num;
	int				node_index;
	int				file_index;

	int shlvl_num;
		// OTHER (?)
		int fd_in; // <
	int				fd_out;
	
}					t_node;


// // Struct qui centralise tout
typedef struct s_minishell
{
	t_env			*env;
	t_env *env_dup;
	t_node			*nodes;
	int				nb_cmd;
	// EXITS
	int				exit;
	int				exit_status;
}					t_minishell;
// utils
char	*get_key_value(t_env *env, char *key);
// EXEC FUNCTIONS
void				perror_handler(char *type);
void				exec(t_node *list, t_minishell *data);
char				*get_cmd_path(char *cmd, t_minishell *data);
char				*get_path_value(t_minishell *data, char *key);
char				**create_char_env(t_env *env);
void				exec_pipe(t_node *nodes, t_minishell *data);
void				heredoc(char *eof, char *file_name_in);
void				exec_simple_cmd(t_minishell *data, t_node *list);
int					is_built_in(t_node *list);
void				handle_redir(t_node *redir);
int					check_if_redir(t_node *node);
void				exec_built_in(t_minishell *data, t_node *list);
// BUILTINS
void				ft_exit(t_minishell *data, t_node *node, char **args);
void				ft_pwd(t_minishell *data, t_node *node, char **args);
void				ft_echo(t_minishell *data, t_node *node, char **args);
void				ft_cd(t_minishell *data, t_node *node, char **args);
void				ft_env(t_minishell *data, t_node *node, char **args);
void				ft_unset(t_minishell *data, t_node *node, char **args);
void				ft_export(t_minishell *data, t_node *node, char **args);
// PARSING FUNCTIONS
int					open_quote_check(char *line);
t_token				*tokenize_input(char *line);
int					is_space(char *line);
char				*create_token(char *str, int start, int end);
char				*create_token(char *str, int start, int end);
char				*remove_quotes(const char *line);
int					ft_strcmp(char *s1, char *s2);
int					tokenizer(char *line, t_node **nodes, t_minishell *mini);
void				free_minishell(t_minishell *mini, t_node *list);
void				free_env_list(t_env *env_list);
int					init_env(t_minishell *data, char **env);
void				print_env(t_env *list);
void				free_tokens(t_token *tokens);
void				extract_substring(char *token, int start, int end,
						char **final_str);
int					is_alpha_underscore(int c);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_itoa(int n);
int					is_brace_expansion(char *token, int *i, char **final_str);
void				ft_putstr_fd(char *s, int fd);
int					special_tokens(char *input, t_token **tokens, int index);
t_token				*new_token(t_token_type type, char *value);
int					word_token(char *input, t_token **tokens, int index);
void				add_token_to_list(t_token **tokens, t_token *new_token);
char				*expand_variables(char *token);
char				*ft_strcpy(char *dest, const char *src);
void				close_quote_check(int *dq, int *sq, int *index, char c);
int					count_arguments(t_token *tokens);
void				free_nodes(t_node *list);
void				get_tmp_file(t_node *node);
void				free_nodes(t_node *list);
int					check_line(char **line);
int					is_space(char *line);
bool				is_quote(char c);
char				*collapse_spaces(char *str);
void				init_parsing(t_node *node);
void				set_cmd(t_token *tokens, t_node *node);
int					init_args(t_token *tokens, t_node *node);
void				update_tokens(t_token **tokens, t_node *node);
char				*remove_quotes_from_word(char *word);
void				set_cmd(t_token *tokens, t_node *node);
void				set_filename(t_token **tokens, t_node *node);
int					list_new_elem_str(t_env **new, char *elem);
void				free_t_env(t_env *env);
int					parse_key_value(t_env **new, char *elem);
char				*duplicate_string(const char *src);
int					special_tokens(char *input, t_token **tokens, int index);
void				count_heredocs(t_token **tokens, t_node *node);
void				count_redir_in(t_token **tokens, t_node *node);
void				count_redir_out(t_token **tokens, t_node *node);
void				allocate_memory_for_filename_out(t_node *node);
void				allocate_memory_for_filename_in(t_node *node);
void				allocate_memory_for_limiter_hd(t_node *node);
void				process_heredoc_tokens(t_token *tokens, t_node *node);
void				process_filename_out(t_token *tokens, t_node *node);
void				process_filename_in(t_token *tokens, t_node *node);
void	count_redirections(t_token **tokens, t_node *node);
void	process_filenames(t_token *tokens, t_node *node);
void	allocate_memory_for_filenames(t_node *node);
void	set_expansions(t_token *tokens, t_node *node);
void	fill_expansions(t_token *tokens, t_node *node);
int	count_expansions(t_token *tokens);
void	process_expansions(t_token **tokens);
int	tokenizer(char *line, t_node **nodes, t_minishell *mini);
void	parse_tokens(t_token *tokens, t_node *node, t_minishell *mini);
char *get_expansion(t_minishell *data, char *key_expansion);
void set_expansions(t_token *tokens, t_node *node);
int init_env_dup(t_minishell *data, char **env);
int append(t_env **list, char *elem);
void add_first(t_env **list, t_env *new);
void print_env(t_env *list);
int list_new_elem_str(t_env **new, char *elem);
t_env *allocate_new_env(void);
void free_t_env(t_env *env);
int parse_key_value(t_env **new, char *elem);
void ft_split_pipes_spaces(char *line, t_node **tokens_list);
int is_only_tabs(char *str);

	// LIBFT FUNCTIONS
	void *ft_lstdelone(void *lst);
char				**ft_split(char const *s, char c);
void				free_split(char **split);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strndup(const char *s, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_putendl_fd(char const *s, int fd);
void				ft_lstclear(t_node **lst, void (*del)(void *));
void				ft_lstadd_back(t_node **lst, t_node *new);
t_node				*ft_lstnew(void *content);
char				*ft_substr(char const *s, unsigned int start, size_t len);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_bzero(void *s, size_t bytes);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_bzero(void *s, size_t bytes);
char				*ft_strdup(const char *s);
int					ft_lstsize(t_node *lst);
size_t				count_args(char **args);
char				*ft_strchr(const char *s, int c);
int					ft_isdigit(char *c);
void				*ft_calloc(size_t count, size_t size);
char				*trim_whitespace(char *str);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char *ft_strstr(char *str, char *to_find);
char *ft_strncpy(char *dest, char *src, unsigned int n);
char *ft_strcat(char *dest, char *src);
size_t ft_itoa_str(int value, char *str);

	// USEFUL FUNCTIONS FOR DEBUG
	void print_node(t_node *head);
int					is_alpha_underscore(int c);

#endif
