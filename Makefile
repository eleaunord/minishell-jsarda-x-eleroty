NAME		=	minishell

SRCS_FILES	= parsing/environment/env_utils.c \
			parsing/environment/init_env.c \
			parsing/environment/init_envdup.c \
			parsing/environment/init_envnull.c \
			parsing/environment/alloc_env.c \
			parsing/environment/key_value.c \
			parsing/parse/checkers.c \
			parsing/expansion/expan_utils.c \
			parsing/expansion/expansion.c \
			parsing/expansion/expand_var.c \
			parsing/expansion/extract_var.c \
			parsing/parse/file_in.c \
			parsing/parse/file_out.c \
			parsing/parse/free.c \
			parsing/expansion/get_expansion.c \
			parsing/parse/heredoc.c \
			parsing/parse/init_parsing.c \
			parsing/parse/main_parse.c \
			parsing/parse/parser.c \
			parsing/parse/debug_fonction.c \
			parsing/parse/remove_quotes.c \
			parsing/parse/signals.c \
			parsing/parse/update_tokens.c \
			parsing/tokenization/collapse_spaces.c \
			parsing/tokenization/pipes_spaces.c \
			parsing/tokenization/quotes.c \
			parsing/tokenization/special_tokens.c \
			parsing/tokenization/tokenizer.c \
			parsing/tokenization/node_creation.c \
			parsing/tokenization/whitespaces.c \
			parsing/tokenization/word_tokens.c \
			utils/builtins_utils.c \
			utils/ft_errors_exec.c \
			utils/env_utils.c \
			utils/utils.c \
			utils/ft_free.c \
			utils/ft_free_2.c \
			exec/exec.c \
			exec/exec_utils.c \
			exec/exec_utils2.c \
			exec/exec_utils3.c \
			exec/exec_utils4.c \
			builtins/builtins_utils.c \
			builtins/builtins_utils2.c \
			exec/redir_utils.c \
			exec/redir.c \
			exec/simple_cmd.c \
			builtins/ft_pwd.c \
			builtins/ft_cd.c \
			builtins/ft_exit.c \
			builtins/ft_env.c \
			builtins/ft_echo.c \
			builtins/ft_export.c \
			builtins/ft_unset.c \
			exec/pipe_exec.c \
			exec/pipe_utils.c \
			exec/pipe_utils2.c \
			exec/mid_exec.c \
			exec/first_exec.c \
			exec/last_exec.c \
			exec/signals.c \
			exec/redir_builtins.c \
			main.c \

SRCS		=	$(addprefix srcs/, $(SRCS_FILES))

INC_FILES	=	minishell.h structs.h
INCS		=	$(addprefix includes/, $(INC_FILES))

CC		=	cc

LIBS		=	-lreadline -Llibft -lft

CFLAGS		=	-Wall -Wextra -Werror -I ./includes -g3
CFLAGSD		=	-Wall -Wextra -Werror -I ./includes -DDEBUG=1 -g3

OBJ_DIR		=	objs/
OBJ_DIRD	=	objsd/

OBJS		=	$(addprefix $(OBJ_DIR), $(SRCS_FILES:.c=.o))
OBJSD		=	$(addprefix $(OBJ_DIRD), $(SRCS_FILES:.c=.o))

DEP		=	$(OBJS:.o=.d)
DEPD		=	$(OBJSD:.o=.d)

NAME		=	minishell

all:		$(NAME)

$(NAME):	$(OBJS)
		make -C libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

debug:		$(OBJ_DIRD) $(OBJSD)
		make -C libft
		$(CC) $(CFLAGSD) -o $(NAME) $(OBJSD) $(LIBS)

clean:
		make -C libft clean
		rm -rf $(OBJS) $(DEP) $(OBJ_DIR)
		rm -rf $(OBJSD) $(DEPD) $(OBJ_DIRD)

fclean:		clean
		make -C libft fclean
		rm -rf $(NAME)

re:		fclean all

-include $(DEP)
-include $(DEPD)

$(OBJ_DIR)%.o: srcs/%.c | $(OBJ_DIR)
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIRD)%.o: srcs/%.c | $(OBJ_DIRD)
		mkdir -p $(dir $@)
		$(CC) $(CFLAGSD) -MMD -o $@ -c $<

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)
		mkdir -p $(OBJ_DIR)exec
		mkdir -p $(OBJ_DIR)builtins
		mkdir -p $(OBJ_DIR)parsing/environment
		mkdir -p $(OBJ_DIRD)parsing/expansion
		mkdir -p $(OBJ_DIR)parsing/parse
		mkdir -p $(OBJ_DIR)parsing/tokenization
		mkdir -p $(OBJ_DIR)utils

$(OBJ_DIRD):
		mkdir -p $(OBJ_DIRD)
		mkdir -p $(OBJ_DIRD)exec
		mkdir -p $(OBJ_DIRD)builtins
		mkdir -p $(OBJ_DIRD)parsing/environment
		mkdir -p $(OBJ_DIRD)parsing/expansion
		mkdir -p $(OBJ_DIRD)parsing/parse
		mkdir -p $(OBJ_DIRD)parsing/tokenization
		mkdir -p $(OBJ_DIRD)utils

.PHONY: all clean fclean re debug
