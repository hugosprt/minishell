NAME = minishell

#srcs/builtins/cd.c \
		srcs/builtins/pwd.c \
		srcs/builtins/echo.c \
		srcs/builtins/env.c \
		srcs/builtins/utils_env.c \
		srcs/builtins/export.c \
		srcs/builtins/unset.c \
		srcs/signal/signal.c 
SRCS =	srcs/prompt/prompt.c \
		srcs/main/main.c \
		srcs/builtins/env.c \
		srcs/builtins/utils_env.c \
		


OBJS = ${SRCS:.c=.o}

LIBFT        = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lreadline -g

RM = rm -rf

all:	$(NAME)

$(NAME): ${OBJS}
	$(MAKE) -C libft
	$(CC) -o $(NAME) ${OBJS} $(CFLAGS) ${LIBFT}
	
clean:
	$(MAKE) clean -C libft
	${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} libft/libft.a

re:		fclean all

.PHONY:	all clean fclean re