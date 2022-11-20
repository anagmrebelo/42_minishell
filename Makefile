#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 11:46:14 by mrollo            #+#    #+#              #
#    Updated: 2022/10/17 15:28:40 by mrollo           ###   ########.fr        #
#                                                                              #
#******************************************************************************#
# **************************************************************************** #
# NAME
# **************************************************************************** #

NAME	= minishell

# **************************************************************************** #
# DIRS
# **************************************************************************** #

SRC_DIR			= src

INCLUDE_DIR		= include

LIBS_DIR		= libft

OBJ_DIR			= obj

# **************************************************************************** #
# FILES
# **************************************************************************** #

LIBS			= $(LIBS_DIR)/libft.a

LIBS_HEADERS	= -I $(LIBS_DIR)/include/minishell.h

INC				= -I $(INCLUDE_DIR) $(LIBS_HEADERS)

SRC				= main.c\
				env/init_env.c\
				env/sort_env.c\
				env/env.c \
				env/free_env.c\
				parse/parsing.c\
				parse/token.c\
				parse/quotes.c\
				parse/variables_env.c\
				parse/token_delete.c\
				parse/type.c\
				parse/pipe_separation.c\
				parse/aux_func.c\
				utils/max_len.c\
				utils/join_free.c\
				exec/exec.c

OBJ				= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

DEP				= $(addsuffix .d, $(basename $(OBJ)))

# **************************************************************************** #
#COMPILATION
# **************************************************************************** #

COMPILE			= gcc -c
LINK			= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD $(INC)
LIBC			= ar -rcs
RM_FILE			= rm -f
RM_DIR			= rm -rf
MKDIR			= mkdir -p

# **************************************************************************** #
#RULES

# **************************************************************************** #

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@$(MKDIR) -p $(dir $@)
				@$(COMPILE) $(CFLAGS) -o $@ $<
				@ECHO "Compiling... $^"

all:			make_libs $(NAME)

make_libs:
			@make -s -C $(LIBS_DIR)

-include $(DEP)

$(NAME):	$(OBJ) $(LIBS)
			@$(LINK) $(OBJ) $(LIBS) -o $(NAME) -lreadline
			@ECHO "Created minishell (mandatory)"

-include $(DEP_BONUS)

clean:
			@$(RM_FILE) $(OBJ)
			@$(RM_DIR)  $(OBJ_DIR)
			@make clean -C $(LIBS_DIR)

fclean:		clean
			@$(RM) $(NAME) $(NAME_BONUS)
			@make fclean -C $(LIBS_DIR)
			@ECHO "Minishell cleaned"

re:			fclean all

.PHONY:		all bonus clean fclean re
