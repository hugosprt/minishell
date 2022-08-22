NAME = minishell

SRCS =	builtins/cd.c \
		builtins/pwd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/utils_env.c \
		builtins/export.c \
		builtins/unset.c \
		signal/signal.c


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