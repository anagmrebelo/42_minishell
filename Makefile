# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:12:42 by arebelo           #+#    #+#              #
#    Updated: 2023/02/08 19:23:08 by arebelo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
# **************************************************************************** #
BINARY				= minishell

# FILES
# **************************************************************************** #
SRCS				= main.c\
					env/init_env.c\
					env/aux_env.c\
					env/sort_env.c\
					env/env.c\
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
					expansions/clean_dollar.c\
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
					builtins/export/export.c\
					builtins/export/aux_exp.c\
					builtins/unset.c\
					builtins/exit.c\
					errors/print_error.c\
					errors/common_errors.c\
					utils/double_array.c\
					utils/join_free.c\
					utils/char_check.c\
					signal.c

OBJS				=${addprefix ${OBJS_DIR}, ${SRCS:.c=.o}}
DEPS				=${addprefix ${OBJS_DIR}, ${SRCS:.c=.d}}

# DIRECTORY
# **************************************************************************** #
READLINE_DIR		= aitor
LIBFT_DIR			= libft
OBJS_DIR			= objs/
SRCS_DIR			= srcs/

# LIBRARIES
# **************************************************************************** #
LIBS_EXEC			= $(LIBFT_DIR)/libft.a
LIBS_EXEC			+= $(READLINE_DIR)/libreadline.a
LIBS_EXEC			+= $(READLINE_DIR)/libhistory.a
LIBS				= -L $(READLINE_DIR) -lhistory -lreadline -ltermcap
INCLUDE				= -I include -I $(READLINE_DIR)

# COMPILATION
# **************************************************************************** #
LINK				= gcc
CC					= gcc -c
DEPFLAGS			= -MMD -MP
CFLAGS				= -Wall -Wextra -Werror 
CFLAGS 				+= -Wpedantic -Werror=pedantic -pedantic-errors -Wcast-align
CFLAGS 				+= -Wcast-qual -Wdisabled-optimization -Wformat=2 -Wuninitialized
CFLAGS 				+= -Wmissing-include-dirs -Wredundant-decls -Wshadow
CFLAGS 				+= -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option
CFLAGS 				+= -fstack-protector-all
RM					= rm -rf

# RULES
# **************************************************************************** #
all:	make_libft make_readline $(BINARY)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) $< -o $@

make_libft:
					make -C $(LIBFT_DIR)

make_readline:	$(READLINE_DIR)/libreadline.a $(READLINE_DIR)/libhistory.a	

$(READLINE_DIR)/libreadline.a: $(READLINE_DIR)/libhistory.a

$(READLINE_DIR)/libhistory.a:
					@pwd $(TMP)
					@cd $(READLINE_DIR) && ./configure
					@make -C $(READLINE_DIR)
					@cd $(TMP)

$(BINARY): $(OBJS) $(LIBS_EXEC)
					@$(LINK) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBS)

clean:
					@$(RM) $(OBJS_DIR)
					@$(RM) .hdoc
					@make clean -s -C $(READLINE_DIR)
					@make clean -s -C $(LIBFT_DIR)

fclean: clean
					@$(RM) $(BINARY)
					@make fclean -s -C $(LIBFT_DIR)

re: fclean all

-include ${DEPS}

.PHONY: all bonus clean fclean re