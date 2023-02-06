/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/04 01:28:09 by arebelo          ###   ########.fr       */
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
	int			error;
}	t_master;

//MAIN
void	readline_loop(t_master *master);
_Bool	isatty_check(t_master *master);

//PIPES
void	minishell(t_master *master);
void	wait_childs(t_master *master);

//ENVIROMENT
void	begin_env(char **environment, t_master *master);
int		init_env(t_master *master, char **enviroment);
t_env	*new_env(char *title, char *value, t_master *master);
char	*get_title(char *str, t_master *master);
char	*get_value(char *str, t_master *master);
void	add_back(t_env *env, t_env *new);
t_env	*last_env(t_env *env);
void	print_env(t_env *env);
void	free_env(t_env *item);
void	free_env_lst(t_env *list);
char	**env_to_array(t_master *master);
int		env_len(t_env *env);
void	free_array(char **array);
void	free_array_master(char **array, t_master *master);
void	sort(char **sort_array, int len);
char	**sort_env_array(char **sort_array, t_master *master, int len);
void	print_sort_env(t_master *master);
char	*getvar_value(t_master *master, char *title);
char	*getvar_value_env(char **env, char *title);
int		default_env(t_master *master);
int		find_in_env(t_env *env, char *str);
void	update_shlvl(t_master *master);
void	var_update(t_master *master);
void	create_shlvl(t_master *master);

//PARSING
_Bool	parsing(t_master *master);
int		tokenize(char *line, t_master *master);
int		aux_tokenize(char *line, int i);
t_token	*new_token(char *line, int size, t_master *master);
char	*env_update(char *read, t_master *master, char *line);
char	*aux1_env(char *read, t_master *master, char *line, int *c);
char	*aux2_env(char *read, t_master *master, char *line, int *c);
char	*aux3_env(char *read, t_master *master, char *line, int *c);
char	*aux4_env(char *read, t_master *master, char *line, int *c);
_Bool	aux5_env(char *read, int *c);
char	*find_var(char *str, t_master *master, int pos, char *full_line);
char	*find_aux(char *str, t_master *master);
char	*find_aux2(char *str, t_master *master);
char	*clean_dollar(char *str, int i, t_master *master, char *fre);
char	*remove_dollar(char *str, t_master *master);
void	home_join(t_token *new, t_master *master, unsigned int i);
void	home_update(t_token *new, t_master *master);
_Bool	is_valid_path(char *str, t_master *master);
void	users_join(t_token *new, t_master *master, unsigned int i);
_Bool	is_dots(char *cmd);
void	del_update(t_token *new);
_Bool	ok(char c);
char	*quotes_clean(t_token *new, t_master *master);
void	quotes_update(t_token *new, t_master *master);
_Bool	check_quotes(char *line);
_Bool	check_syntax(t_master *master);
_Bool	check_exceptions(t_token *fst_ty, t_token *scnd_ty);
_Bool	syntax_verifications(t_token *temp, t_master *master);
void	add_type(t_token *new);
void	add_types_redir(t_master *master);
void	check_heredoc(t_master *master);
void	add_list(t_master *list, t_token *item);
t_token	*last_token(t_token *token);
t_token	*first_token(t_token *token);
t_token	*copy_token(t_token *src, t_master *master);
int		list_len(t_token *token);
void	free_token(t_token *item);
void	free_token_list(t_token *ls);
void	clean_tokens(t_master *master);
void	delete_token(t_token *token, t_master *master);
void	free_commands(t_master *master);
void	free_command(t_command *pipe);
void	prep_next_line(t_master *master);
int		command_separation(t_master *master);
t_token	*adding_sort(t_token *temp, t_command *cmd,
			t_master *master, int cmd_nb);
int		count_commands(t_master *master);
void	add_to_command(t_token *member, t_token **list, t_master *master);
void	insert_in_list(t_command *member, t_master *master);
t_token	*find_next_pipe(t_token *temp);
_Bool	is_delimeter(char c);
_Bool	is_space(char c);
char	*create_str(char *str, t_env *temp, t_master *master);

//EXEC ONE COMMAND
void	minishell_one(t_master *master);
void	exec_one(t_master *master, t_command *cmd);
void	exec_bin_one(t_master *master, t_command *cmd);
void	exec_aux_free(t_command *cmd, t_master *master);

//EXECUTE MULTI
void	child(t_master *master, t_command *cmd);
void	parent(t_master *master);
void	minishell_multi(t_master *master);

void	exec_bin(t_master *master, t_command *cmd);
int		exec(t_master *master, t_command *cmd);
int		is_builtin(char *command);
int		exec_builtin(char *command, t_command *cmd,
			t_env *env, t_master *master);
void	exec_aux_bin_free(char *command, char**path, char **env,
			t_master *master);

//EXEC UTILS
char	**find_path(t_master *master);
char	*get_command(char **path, char *cmd, t_master *master);
char	**token_to_array(t_token *token, t_master *master);
_Bool	check_path(char **path, char *cmd, t_master *master);
char	*executable(char *cmd, t_master *master);
_Bool	is_path(char *cmd);
_Bool	path_bin(char **path);
void	free_path_master(char *aux, char **path, t_master *master,
			int exit_code);

//HEREDOC pasarlo a parsing
void	handle_heredoc(t_token *token, char *limit, t_master *master);
char	*heredoc_update(char *read, t_master *master);
char	*find_here(char *str, t_master *master, int pos, char *full_line);

//REDIRECTIONS
void	init_redirs(t_master *master);
void	init_pipe(t_master *master);
void	close_init_redirs(t_master *master);
void	handle_redirs(t_command *cmd, t_master *master);
void	handle_pipe(t_master *master, t_command *cmd);
void	handle_outputs(t_command *cmd, t_master *master);
void	redir_inputs(t_command *cmd, t_master *master);
void	redir_outputs(t_command *cmd, t_master *master);
_Bool	validate_input(t_token *temp, t_command *cmd, t_master *master);
_Bool	validate_output(char *str, t_command *cmd, t_master *master);
char	*file_new_path(char *str, t_master *master);
_Bool	check_path_tofile(char *str, t_command *cmd, t_master *master);
void	reset_redirs(t_master *master);

//BUILTINS
int		ft_echo(char **args);
void	print_echo(char *str, int fd);
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
int		ft_exit(char **args, t_master *master);

//ERRORS
void	print_error(char *minishell, char *builtin, char *message);
char	*create_message(t_master *master, char *message,
			char *token, char *msg);
void	no_file_dir(t_master *master, char *cmd, int exit_code);
void	perm_denied(t_master *master, char *cmd, int exit_code);
void	not_dir(t_master *master, char *cmd, int exit_code);

//FREE
void	free_master(t_master *master);
void	free_line(t_master *master);
void	clean_free(t_master *master, int exit_code);
void	clean_free_no_exit(t_master *master);
void	free_fail_exec(char *command, char **path, char **env);

//UTILS
char	*join_free(char *s1, char *s2);
void	free_double_array(char **table);
size_t	ft_strlen(const char *str);
char	**copy_double_array(char **src);
char	*join_double_free(char *s1, char *s2);
char	*join_free_s1(char *s1, char *s2);
char	*join_free_s2(char *s1, char *s2);
char	*free_aux_join(char *s1, char *s2, char *s3);
_Bool	is_dots(char *cmd);
char	*free_aux_join(char *s1, char *s2, char *s3);
char	*free_aux_master(char *s1, char *s2, char *s3, t_master *master);

//signal
void	init_signal(int i);

#endif
