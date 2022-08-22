# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpol <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/30 02:20:09 by rpol              #+#    #+#              #
#    Updated: 2021/11/30 04:41:19 by rpol             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	  ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
	  ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	  ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
	  ft_tolower.c ft_toupper.c
OBJ = ${SRC:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror

AR = ar -cr

RM = rm -f

NAME = libft.a

all: ${NAME}

.c.o:
		${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	${AR}  ${NAME} ${OBJ}

clean:
		${RM} ${OBJ}

fclean:	clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
