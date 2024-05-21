NAME        := minishell
CC        := clang
CFLAGS    := -Wall -Wextra -Werror -g3
LIBS = -lreadline
SRCS        :=   libft/ft_lst.c \
					libft/ft_substr.c \
					libft/ft_str.c \
					libft/ft_utils.c \
					srcs/parsing/tokenization/tokens.c \
					srcs/parsing/tokenization/pipes_spaces.c \
					srcs/parsing/tokenization/quotes.c \
					# parsing/tokenization/operators.c \

OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} $(LIBS)
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
	rm -f $(OBJS) $(TARGET)