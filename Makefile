NAME		=	minishell

SRCS_FILES	=	parsing/expander.c \
			parsing/expander_utils.c \
			parsing/parsing.c \
			parsing/env_init.c \
			parsing/debug_function.c \
			parsing/parsing_add_spaces.c \
			parsing/parsing_block_redir.c \
			parsing/parsing_count_operators.c \
			parsing/parsing_syntax.c \
			parsing/parsing_syntax_2.c \
			parsing/parsing_block.c \
			parsing/parsing_block_utils.c \
			utils/ft_split_quotes.c \
			utils/ft_split_quotes_utils.c \
			utils/builtins_utils.c \
			utils/ft_errors_parsing.c \
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
	mkdir -p objs/exec
	mkdir -p objs/builtins
	mkdir -p objs/parsing
	mkdir -p objs/utils

# objsd/%.o	: srcs/%.c includes/minishell.h
# 	mkdir -p objsd
# 	$(CC) $(CFLAGSD) -MMD -o $@ -c $<

.PHONY: all clean fclean re
