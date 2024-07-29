/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:12:24 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/29 17:12:27 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define NUM_OF_BUILT_INS 7

# ifndef DEBUG
#  define DEBUG 0
# endif

/*			DEBUG			*/

// MINISHELL STRUCT
typedef enum e_token_type
{
	TOKEN_WORD,      // = 0
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
	int					processed;
	char				*key_expansion;
	int					limiter_hd_count;
}						t_token;

// Env struct
typedef struct s_env
{
	char				*str;
	char				*key;
	char				*value;
	int					shlvl_num;
	struct s_env		*next;
}						t_env;

// NODES (from parsing to exec, with love)
typedef struct s_node // t_data
{
	// Making the nodes (for parsing)
	struct s_node *next;
	void *content;

	// Dealing with tokens (for parsing)
	struct s_token *tokens_in_node;

	// From parsing to exec
	char *cmd;
	char **args;
	int arg_count;

	char **key_expansion; // in args
	int expansion_count;
	int lonely_expansion;

	char **filename_in;
	char **filename_out;
	int file_in_count;  // count in (for parsing)
	int file_out_count; // count out (for parsing)
	int fdout;          // init to -1 in parsing if redir out
	int fdin;           // init to -1 in parsing if redir in
	int fdintmp;
	int is_redir_in;   // is there a redir in ? 1 : yes, 0 : no
	int is_redir_out;  // is there a redir out ? 1 : yes, 0 : no
	int is_here_doc;   // is there a here doc ? 1 : yes, 0 : no
	int is_append;     // to do => fdout too ?
	char **limiter_hd; // eof
	int limiter_hd_count;
	char *last_heredoc;
	char *path;

	int pid;
	int error_num; // statu

}						t_node;

// // Struct qui centralise tout
typedef struct s_minishell
{
	t_env				*env;
	t_env				*env_dup;
	t_node				*nodes;
	int					pipes[2];
	int					exit_status;
}						t_minishell;

// EXEC
int						exec(t_minishell *shell);
void					first_exec(t_minishell *shell, t_node *data);
void					last_exec(t_minishell *shell, t_node *data);
void					middle_exec(t_minishell *shell, t_node *data,
							int fd_tmp);
void					exec_pipe(t_minishell *shell, int num_cmd);
void					exec_simple_cmd(t_node *data, t_minishell *shell);

// EXEC_UTILS
void					handle_redir(t_minishell *shell, t_node *data);
char					*get_key_value(t_env *env, char *key);
int						check_key(t_env *env, char *key);
void					ft_errors_exec(int err, char *msg, char *supp,
							int err_status);
void					ft_print_exp(t_env *exp, t_node *data);
void					readline_loop(char *eof, int fd);
void					ft_wait_hd(t_node *data);
int						get_tmp_file(t_node *datas);
int						is_built_in(t_node *data);
int						check_if_redir(t_node *datas);
void					exec_built_in(t_node *datas, t_minishell *shell);
void					ft_dup(t_node *data);
char					*get_path_value(t_minishell *datas, char *key);
char					**create_char_env(t_env *env, int env_size);
int						get_env_list_size(t_env *list);
void					handle_heredoc(t_minishell *shell, t_node *data);
void					ft_wait(t_node *data);
char					*get_cmd_path(t_node *data, t_minishell *shell);
int						ft_lstsize_cmd(t_node *lst);
void					ft_close(t_node *data);
void					close_fd(t_node *data);
void					manage_no_path(t_node *head, t_minishell *shell,
							int mod);
void					exit_first_child(t_node *data, t_minishell *shell);
void					exit_other_child(t_node *data, t_minishell *shell);
void					manager_mid(t_node *data, t_minishell *shell,
							int fd_tmp);
void					execve_fail(void);
void					heredoc(t_node *data, t_minishell *shell, char *eof,
							char *file_name);
int						dir_error(char *cmd);
// BUILTINS
void					ft_cd(t_node *data, t_minishell *shell, char **args);
void					ft_echo(t_node *data, t_minishell *shell, char **args);
void					ft_env(t_node *data, t_minishell *shell, char **args);
void					ft_exit(t_node *data, t_minishell *shell, char **args);
void					ft_export(t_node *data, t_minishell *shell,
							char **args);
void					ft_pwd(t_node *data, t_minishell *shell, char **args);
void					ft_unset(t_node *data, t_minishell *shell, char **args);

// BUILTINS UTILS
unsigned long long int	ft_atoll(const char *str, int *overflow);
int						is_valid_identifier(const char *name);
int						heredoc_builtins(t_node *data, t_minishell *shell,
							char *eof, char *file_name);
int						handle_redir_builtins(t_node *data, t_minishell *shell,
							int i);
void					ft_lstadd_back_env(t_env **alst, t_env *new);
t_env					*ft_lstnew_env(char *line, char *name, char *value);

void					debug_print_block(t_node **list);
// SIGNALS
void					handler_sig_cmd(int sig);
void					manage_sig(void);

// utils
void					free_var_env(t_env *node);
void					free_mini(t_minishell *data);
void					setup_signal_handlers(void);
void					sigint_handler(int sig);
int						ft_tablen(char **tab);
void					print_env(t_env *env, t_node *data);
void					ft_free_env_list(t_env **env);
void					ft_clear_datas(t_node **datas);
void					free_hd_file(t_node **data, int mode);
void					ft_recup(t_minishell *shell);
void					free_child(t_node *data, t_minishell *shell,
							int exit_status);
size_t					count_args(char **args);

// PARSING FUNCTIONS
int						open_quote_check(char *line);
t_token					*tokenize_input(char *line);
int						is_space(char *line);
char					*remove_quotes(const char *line);
int						ft_strcmp(char *s1, char *s2);
int						tokenizer(char *line, t_node **nodes,
							t_minishell *mini);
void					free_minishell(t_minishell *mini, t_node *list);
void					free_env_list(t_env *env_list);
int						init_env(t_minishell *data, char **env);
void					free_tokens(t_token *tokens);
int						is_alpha_underscore(int c);
void					*ft_memcpy(void *dest, const void *src, size_t n);
char					*ft_itoa(int n);
void					ft_putstr_fd(char *s, int fd);
int						special_tokens(char *input, t_token **tokens,
							int index);
t_token					*new_token(t_token_type type, char *value);
int						word_token(char *input, t_token **tokens, int index);
void					add_token_to_list(t_token **tokens, t_token *new_token);
char					*expand_variables(char *token);
void					close_quote_check(int *dq, int *sq, int *index, char c);
int						count_arguments(t_token *tokens);
void					free_nodes(t_node *list);
void					free_nodes(t_node *list);
int						check_line(char **line);
int						is_space(char *line);
bool					is_quote(char c);
char					*collapse_spaces(char *str);
void					init_parsing(t_node *node);
void					set_cmd(t_token *tokens, t_node *node);
// int						init_args(t_token *tokens, t_node *node);
void					update_tokens(t_token **tokens, t_node *node);
char					*remove_quotes_from_word(char *word);
void					set_cmd(t_token *tokens, t_node *node);
void					set_filename(t_token **tokens, t_node *node);
int						list_new_elem_str(t_env **new, char *elem);
void					free_t_env(t_env *env);
int						parse_key_value(t_env **new, char *elem);
char					*duplicate_string(const char *src);
void					count_heredocs(t_token **tokens, t_node *node);
void					count_redir_in(t_token **tokens, t_node *node);
void					count_redir_out(t_token **tokens, t_node *node);
void					allocate_memory_for_filename_out(t_node *node);
void					allocate_memory_for_filename_in(t_node *node);
void					allocate_memory_for_limiter_hd(t_node *node);
void					process_heredoc_tokens(t_token *tokens, t_node *node);
void					process_filename_out(t_token *tokens, t_node *node);
void					process_filename_in(t_token *tokens, t_node *node);
void					set_expansions(t_token *tokens, t_node *node);
int						count_expansions(t_token *tokens);
void					process_expansions(t_token **tokens);
int						tokenizer(char *line, t_node **nodes,
							t_minishell *mini);
void					parse_tokens(t_token *tokens, t_node *node,
							t_minishell *mini);
char					*get_expansion(t_minishell *data, char *key_expansion);
void					set_expansions(t_token *tokens, t_node *node);
int						init_env_dup(t_minishell *data, char **env);
int						append(t_env **list, char *elem);
void					add_first(t_env **list, t_env *new);
t_env					*allocate_new_env(void);
void					free_t_env(t_env *env);
int						parse_key_value(t_env **new, char *elem);
bool					ft_split_pipes_spaces(char *line, t_node **tokens_list);
int						is_only_tabs(char *str);
void					free_node_cmd_args(t_node *node);
void					init_args(t_token *tokens, t_node *node);
void					ft_putchar_fd(char c, int fd);
void					freetab(char **tab);
int						process_input_line(char *input_line, t_node **node_list,
							t_minishell *data);
void					freelist(t_node **nodes);
char					*trim_whitespace(char *str);
extern int				g_status;
#endif
