# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:12:42 by arebelo           #+#    #+#              #
#    Updated: 2023/02/07 17:42:12 by arebelo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
# **************************************************************************** #
BINARY				= libft.a

# FILES
# **************************************************************************** #
SRCS				= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
						ft_strchr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strlen.c \
						ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strdup.c \
						ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_calloc.c ft_memchr.c \
						ft_memcmp.c ft_strnstr.c ft_atoi.c ft_substr.c ft_strjoin.c \
						ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
						ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
						ft_strcmp.c

OBJS				= ${addprefix ${OBJS_DIR}, ${SRCS:.c=.o}}
DEPS				= ${addprefix ${OBJS_DIR}, ${SRCS:.c=.d}}

# COMPILATION
# **************************************************************************** #
OBJS_DIR			= objs/

# COMPILATION
# **************************************************************************** #
LINK				= gcc
CC					= gcc -c
DEPFLAGS			= -MMD -MP
CFLAGS				= -Wall -Wextra -Werror 
RM					= rm -rf

# RULES
# **************************************************************************** #
all:	$(BINARY)

$(OBJS_DIR)%.o: %.c
					mkdir -p ${OBJS_DIR}
					${CC} $(DEPFLAGS) ${CFLAGS} -I ./ $< -o $@

$(BINARY): $(OBJS) libft.h Makefile
					ar -crs $(BINARY) $(OBJS)

clean:
					@$(RM) $(OBJS_DIR)

fclean: clean
					@$(RM) $(BINARY)

re: fclean all

-include ${DEPS}

.PHONY: all bonus clean fclean re