# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 11:46:14 by mrollo            #+#    #+#              #
#    Updated: 2023/02/01 12:51:54 by arebelo          ###   ########.fr        #
#                                                                              #
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

COMFLAGS		= -I/Users/$(USER)/.brew/opt/readline/include
LINKFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

SRC				= main.c\
				env/init_env.c\
				env/sort_env.c\
				env/env.c \
				env/free_env.c\
				env/return_var.c\
				env/default_env.c\
				env/begin_env.c\
				pipe/pipe_stru.c\
				parse/parsing.c\
				parse/token.c\
				parse/quotes.c\
				parse/token_delete.c\
				parse/copy_token.c\
				parse/delete_update.c\
				parse/type.c\
				parse/command_separation.c\
				parse/free.c\
				parse/free_components.c\
				expansions/variables_env.c\
				expansions/variables_env_aux.c\
				expansions/find_var.c\
				expansions/home_update.c\
				redir/initial_redir.c\
				redir/outputs.c\
				redir/inputs.c\
				exec/exec_one.c\
				exec/exec_multi.c\
				exec/exec_utils.c\
				exec/exec_builtin.c\
				exec/get_command.c\
				exec/exec.c\
				heredoc/heredoc.c\
				heredoc/variables_heredoc.c\
				heredoc/find_var_heredoc.c\
				builtins/echo.c\
				builtins/pwd.c\
				builtins/cd/cd.c\
				builtins/cd/aux_cd.c\
				builtins/env.c\
				builtins/export.c\
				builtins/unset.c\
				builtins/exit.c\
				errors/print_error.c\
				errors/common_errors.c\
				utils/double_array.c\
				utils/join_free.c\
				utils/char_check.c\
				signal.c\
				

OBJ				= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

DEP				= $(addsuffix .d, $(basename $(OBJ)))

# **************************************************************************** #
#COMPILATION
# **************************************************************************** #

COMPILE			= gcc -c
LINK			= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -g $(INC)
LIBC			= ar -rcs
RM_FILE			= rm -f
RM_DIR			= rm -rf
MKDIR			= mkdir -p

# **************************************************************************** #
#RULES

# **************************************************************************** #

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@$(MKDIR) -p $(dir $@)
				@$(COMPILE) $(CFLAGS) $(COMFLAGS) -o $@ $<
				@echo "Compiling... $^"

all:			make_libs $(NAME)

make_libs:
			@make -s -C $(LIBS_DIR)

-include $(DEP)

$(NAME):	$(OBJ) $(LIBS)
			@$(LINK) $(OBJ) $(LIBS) $(LINKFLAGS) -o $(NAME) -lreadline
			@echo "Created minishell (mandatory)"

-include $(DEP_BONUS)

clean:
			@$(RM_FILE) $(OBJ)
			@$(RM_DIR)  $(OBJ_DIR)
			@make clean -C $(LIBS_DIR)

fclean:		clean
			@$(RM) $(NAME) $(NAME_BONUS)
			@make fclean -C $(LIBS_DIR)
			@echo "Minishell cleaned"

re:			fclean all

.PHONY:		all bonus clean fclean re
