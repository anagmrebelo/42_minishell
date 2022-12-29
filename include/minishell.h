/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2022/12/02 14:18:21 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <../libft/libft.h>
# include <sys/types.h> //para portatil en codespaces
# include <sys/wait.h> //para portatil en codespaces

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

typedef struct s_env
{
	char *content;
	char *title;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct  s_token
{
    char            *str;
    int             type;
	int				fd;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;

typedef struct  s_command
{
    int					cmd_nb;
	t_token	            *args;
	t_token	            *inputs;
    _Bool               inv_file;
	t_token             *outputs;
	char	            **args_char;
    struct s_command	*next;
} t_command;

typedef struct s_master
{
    char        *line;
    t_env	    *env;
    t_token	    *token_list;
    int         numCommands;
    t_command	*commands_list;
    int         std_in;
    int         std_out;
    int         fd[2];
	_Bool		status;
	int			pid;
}   t_master;

//MAIN
_Bool	add_hist_exit_check(t_master *master);
void	minishell(char *line, t_master *master);

//SIGNALS
void    init_signal(int i);

//ENVIROMENT
int		init_env(t_master *master, char **enviroment);
t_env	*new_env(char *content, char *title, char *value);
char    *get_title(char *str);
char    *get_value(char *str);
void	add_back(t_env *env, t_env *new);
t_env	*last_env(t_env *env);
void	print_env(t_env *env);
void    free_env(t_env *item);
void    free_env_lst(t_env *list);
char    **env_to_array(t_env *env);
int 	env_len(t_env *env);
void    free_array(char **array);
void	sort(char **sort_array, int len);
char    **sort_env_array(char **sort_array, t_env *env, int len);
void    print_sort_env(t_env *env);


//Parsing
_Bool	parsing(char * line, t_master *master);
int		tokenize(char *line, t_master *master);
t_token *new_token(char *line, int size, t_master *master);

void	env_update(t_token *new, t_master *master);
char	*aux1_env(t_token *new, t_master *master, char *line, int *c);
char	*aux2_env(t_token *new, t_master *master, char *line, int *c);
char	*aux3_env(t_token *new, t_master *master, char *line, int *c);
char	*aux4_env(t_token *new, t_master *master, char *line, int *c);
char	*find_var(char *str, t_master *master, int pos, char *full_line);
char	*find_aux(char *str, t_master *master);
char	*find_aux2(char *str, t_master *master);
_Bool	ok(char c);

char	*quotes_clean(t_token *new, t_master *master);
void	quotes_update(t_token *new, t_master *master);
_Bool	check_quotes(char *line);
_Bool	check_syntax(t_master *master);

void	add_type(t_token *new);
void	add_types_redir(t_master *master);

void	check_heredoc(t_master *master);

void    add_list(t_master *list, t_token *item);
t_token *last_token(t_token *token);
t_token *first_token(t_token *token);
t_token	*copy_token(t_token *src, t_master *master);

void    free_token(t_token *item);
void    free_token_list(t_token *ls);
void	clean_tokens(t_master *master);
void    delete_token(t_token *token, t_master *master);
void	free_commands(t_master *master);
void	free_command(t_command *pipe);
void	prep_next_line(t_master *master);

void	command_separation(t_master *master);
int     count_commands(t_master *master);
void	add_to_command(t_token *member, t_token **list, t_master *master);
void	insert_in_list(t_command *member, t_master *master);

_Bool	is_delimeter(char c);
_Bool	is_space(char c);


//EXEC ONE COMMAND
void	minishell_one(t_master *master);
void	exec_one(t_master *master, t_command *cmd);
void	exec_bin_one(t_master *master, t_command *cmd);
void	exec_aux_free(t_command *cmd, char **path, t_master *master);


//HEREDOC pasarlo a parsing
void     handle_heredoc(t_token *token, char *limit);

//REDIRECTIONS
void    init_redirs(t_master *master);
void	init_pipe(t_master *master);
void    close_init_redirs(t_master *master);
void	handle_redirs(t_command *cmd, t_master *master);
void	handle_pipe(t_master *master, t_command *cmd);
void	handle_outputs(t_command *cmd, t_master *master);
void	redir_inputs(t_command *cmd, t_master *master);
void	redir_outputs(t_command *cmd, t_master *master);
_Bool	validate_file(char *path, t_master *master);
void	reset_redirs(t_master *master);


//EXECUTE
char    **find_path(t_master *master);
char    *get_command(char **path, char *cmd, t_master *master);
char    **token_to_array(t_token *token, t_master *master);
void	exec_bin(t_master *master, t_command *cmd);
int     exec(t_master *master, t_command *cmd);
int     is_builtin(char *command);
void    exec_builtin(char *command, t_command *cmd, t_env *env);
void	exec_aux_bin_free(char *command, char**path, char **env, t_master *master);

//BUILTINS
int     ft_echo(char **args);
void    print_echo(char *str, int fd);
int     ft_pwd(t_env *env);
int     ft_cd(t_env *env, char **args);
char    *get_env_value(char *title, t_env *env);
void    update_env(char *oldpwd, t_env *env);
void    update_pwd(t_env *env);
void    update_oldpwd(char *oldpwd, t_env *env);
void    change_dir(char *arg, char *oldpwd, t_env *env);
void    ft_env(t_env *env);
void    ft_unset(t_env *env, char **args);
int     ft_export(t_env *env, char **args);
void    print_export_error(char *str);

//FREE
void    free_master(t_master *master);
void    free_line(t_master *master);
void	clean_free_pipe_read(t_master *master);
void	clean_free(t_master *master);
void	clean_free_no_exit(t_master *master);
void	free_fail_exec(char *command, char **path, char **env);


//UTILS
char			*join_free(char *s1, char *s2);
unsigned int	find_max_len(char *s1, char *s2);
void	        free_double_array(char **table);
size_t			ft_strlen_null(const char *str);
char			**copy_double_array(char ** src);
char			*join_double_free(char *s1, char *s2);
char			*join_free_s1(char *s1, char *s2);
char			*join_free_s2(char *s1, char *s2);

//Aux to delete before submitting
void    print_list_tokens(t_token *list);
void	print_commands(t_master *master);
size_t	ft_strlcat1(char *dst, const char *src, size_t dstsize);

#endif
