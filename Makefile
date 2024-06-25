NAME        := minishell
CC        := gcc
CFLAGS    := -Wall -Wextra -Werror -g3
LIBS = -lreadline
SRCS        :=   libft/ft_lst.c \
					libft/ft_substr.c \
					libft/ft_str.c \
					libft/ft_utils.c \
					libft/ft_strcmp.c \
					libft/ft_split.c \
					libft/ft_putstr_fd.c \
					libft/ft_lstdelone.c \
					libft/ft_alloc.c \
					libft/ft_itoa.c \
					libft/ft_strtrim.c \
					libft/ft_copy.c \
					libft/ft_strcat.c \
					libft/ft_strstr.c \
					libft/ft_strncpy.c \
					srcs/parsing/tokenization/word_tokens.c \
					srcs/parsing/tokenization/special_tokens.c \
					srcs/parsing/parse/main_loop.c \
					srcs/parsing/parse/parser.c \
					srcs/parsing/tokenization/pipes_spaces.c \
					srcs/parsing/tokenization/quotes.c \
					srcs/parsing/tokenization/tokenizer.c \
					srcs/parsing/environment/env.c \
					srcs/parsing/environment/key_value.c \
					srcs/parsing/parse/free.c \
					srcs/parsing/environment/alloc_env.c \
					srcs/parsing/parse/get_expansion.c \
					srcs/parsing/parse/checkers.c \
					srcs/parsing/parse/filename.c \
					srcs/parsing/parse/expansion.c \
					srcs/parsing/parse/init_parsing.c \
					srcs/parsing/parse/count_expansions.c \
					srcs/parsing/parse/remove_quotes.c \
					srcs/parsing/parse/update_tokens.c \
					srcs/parsing/tokenization/collapse_spaces.c \
					srcs/parsing/tokenization/whitespaces.c \
					srcs/exec/simple_command_exec.c \
					srcs/exec/env_utils.c \
					srcs/exec/redir.c \
					srcs/exec/exec.c \
					srcs/exec/get_env_path.c \
					utils/perror.c \
					utils/ft_free.c \
					utils/count.c \
					utils/utils.c \
					srcs/builtins/ft_echo.c \
					srcs/builtins/ft_env.c \
					srcs/builtins/ft_pwd.c \
					srcs/builtins/ft_export.c \
					srcs/builtins/ft_cd.c \
					srcs/builtins/ft_exit.c \
					srcs/builtins/ft_unset.c \
					srcs/exec/pipe_exec.c \


OBJS        := $(SRCS:.c=.o)

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@${CC} ${CFLAGS} -o ${NAME} ${OBJS} $(LIBS)
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
	@rm -f $(OBJS)
	@echo "$(RED)Cleaned object files${CLR_RMV}"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Cleaned all build files${CLR_RMV}"

re: fclean all

.PHONY: all clean fclean re
