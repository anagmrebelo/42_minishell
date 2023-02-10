/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/10 13:31:15 by anarebelo        ###   ########.fr       */
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

//ENVIROMENT
void	begin_env(char **environment, t_master *master);
int		init_env(t_master *master, char **enviroment);
t_env	*new_env(char *title, char *value, t_master *master);
char	*get_title(char *str, t_master *master);
char	*get_value(char *str, t_master *master);
void	add_back(t_env *env, t_env *new);
void	print_env(t_env *env);
void	free_env(t_env *item);
void	free_env_lst(t_env *list);
char	**env_to_array(t_master *master);
int		env_len(t_env *env);
void	free_array(char **array);
void	free_array_master(char **array, t_master *master);
void	print_sort_env(t_master *master);
char	*getvar_value(t_master *master, char *title);
char	*getvar_value_env(char **env, char *title);
int		default_env(t_master *master);
int		find_in_env(t_env *env, char *str);
void	update_shlvl(t_master *master);
void	var_update(t_master *master);
void	create_shlvl(t_master *master);

//BUILTINS
int		ft_echo(char **args);
int		ft_pwd(t_env *env);
int		ft_cd(t_env *env, char **args, t_master *master);
char	*get_env_value(char *title, t_env *env);
void	update_env(char *oldpwd, t_env *env, t_master *master);
int		update_pwd(t_env *env, t_master *master);
void	update_oldpwd(char *oldpwd, t_env *env, t_master *master);
int		change_dir(char *arg, char *oldpwd, t_env *env, t_master *master);
int		ft_env(t_env *env);
int		ft_unset(t_env *env, char **args);
int		ft_export(t_env *env, char **args, t_master *master);
void	add_to_env(char *title, char *value, t_master *master);
void	print_export_error(char *str);
int		first_check(char *str);
int		var_title_check(char *str);
int		ft_exit(char **args, t_master *master);

//signal
void	init_signal(int i, t_env *env);

#endif
