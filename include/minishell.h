/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/10 17:58:30 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <../libft/libft.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# define READLINE_LIBRARY 1
# include "readline.h"
# include "history.h"

# define ARG 0
# define OUTPUT 1
# define APPEND 2
# define INPUT 3
# define HEREDOC 4
# define PIPE 5

# define READ 0
# define WRITE 1

# define I 0
# define J 1

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

int	g_error;
int	g_ctrlc;

typedef struct s_env
{
	char			*title;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	int				fd;
	_Bool			no_del;
	_Bool			here;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_command
{
	int					cmd_nb;
	t_token				*args;
	t_token				*inputs;
	_Bool				inv_file;
	_Bool				inv_perm;
	_Bool				not_dir;
	t_token				*failed;
	t_token				*outputs;
	char				**args_char;
	struct s_command	*next;
}	t_command;

typedef struct s_master
{
	char		*line;
	t_env		*env;
	t_token		*token_list;
	int			num_commands;
	t_command	*commands_list;
	int			std_in;
	int			std_out;
	int			fd[2];
	_Bool		status;
	int			pid;
}	t_master;

//signal
void	init_signal(int i, t_env *env);

#endif
