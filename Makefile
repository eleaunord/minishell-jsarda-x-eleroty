NAME		=	minishell

SRCS_FILES	= parsing/environment/env.c \
			parsing/environment/alloc_env.c \
			parsing/environment/key_value.c \
			parsing/parse/checkers.c \
			parsing/parse/count_expansions.c \
			parsing/parse/expansion.c \
			parsing/parse/file_in.c \
			parsing/parse/file_out.c \
			parsing/parse/free.c \
			parsing/parse/get_expansion.c \
			parsing/parse/heredoc.c \
			parsing/parse/init_parsing.c \
			parsing/parse/main_parse.c \
			parsing/parse/parser.c \
			parsing/parse/remove_quotes.c \
			parsing/parse/signals.c \
			parsing/parse/update_tokens.c \
			parsing/tokenization/collapse_spaces.c \
			parsing/tokenization/pipes_spaces.c \
			parsing/tokenization/quotes.c \
			parsing/tokenization/special_tokens.c \
			parsing/tokenization/tokenizer.c \
			parsing/tokenization/tokens.c \
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

INC_FILES	=	 minishell.h structs.h

INCS	=	$(addprefix includes/, $(INC_FILES))

CC		=	cc

LIBS		=	-lreadline -Llibft -lft

CFLAGS		=	-Wall -Wextra -Werror -I ./includes -g3

OBJ_DIR =	objs/

OBJS_FILES	=	$(SRCS_FILES:%.c=%.o)
# OBJS_FILESD	=	$(SRCS_FILES:%.c=%.o)

OBJS	=	$(addprefix $(OBJ_DIR), $(OBJS_FILES))
# OBJSD		=	$(addprefix objsd/, $(OBJS_FILES))

DEP		=	$(OBJS:%.o=%.d)
# DEPD		=	$(OBJSD:%.o=%.d)

# CFLAGSD	=	-Wall -Wextra -Werror -D DEBUG=1 -g3

all:		$(NAME)

$(NAME)	:	$(OBJS)
		make -C libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)


# debug:		${OBJSD}
# 			make -C libft
# 			${CC} ${CFLAGSD} -o ${NAME} ${OBJSD} $(LIBS)

clean:
	make -C libft clean
	rm -rf $(OBJS) $(DEP)
	rm -rf objs/
	#rm -rf $(OBJSD) $(DEPD)
	#rm -rf objsd/

fclean:		clean
		make -C libft fclean
		rm -rf $(NAME)

re		:	fclean all

-include $(DEP)

objs/%.o	: srcs/%.c | $(OBJ_DIR)
			mkdir -p objs
			$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)exec
	mkdir -p $(OBJ_DIR)builtins
	mkdir -p $(OBJ_DIR)parsing/environment
	mkdir -p $(OBJ_DIR)parsing/parse
	mkdir -p $(OBJ_DIR)parsing/tokenization
	mkdir -p $(OBJ_DIR)utils

# objsd/%.o	: srcs/%.c includes/minishell.h
# 	mkdir -p objsd
# 	$(CC) $(CFLAGSD) -MMD -o $@ -c $<

.PHONY: all clean fclean re
