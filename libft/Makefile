#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 20:02:07 by mrollo            #+#    #+#              #
#    Updated: 2022/01/28 17:35:00 by mrollo           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
		ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c ft_strdup.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
		ft_strncmp.c ft_strrchr.c ft_strnstr.c ft_strtrim.c ft_substr.c \
		ft_split.c ft_tolower.c ft_toupper.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

INCLUDE = libft.h

CC = gcc
RM = rm -f
AR = ar rcs
RN = ranlib
CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${BONUS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}
			${RN} ${NAME}

bonus:		${OBJS} ${OBJS_BONUS}
			${AR} ${NAME} ${OBJS} ${OBJS_BONUS}
			${RN} ${NAME}

clean:
			${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
			${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
