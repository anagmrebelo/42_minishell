/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:18:50 by mrollo            #+#    #+#             */
/*   Updated: 2023/01/28 22:05:20 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Toma la variable $PATH y la separa (con split)

char    **find_path(t_master *master)
{
    char **path;
    t_env *tmp;

    path = NULL;
    tmp = master->env;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->title, "PATH") == 0)
        {
            path = ft_split(tmp->value, ':');
			if(!path)
				clean_free(master, 1);
            break;
        }
        tmp = tmp->next;
    }
    return (path);
}

/**
 * Checks if it can't find the file, if it is a directory and if it has the correct permissions to execute
*/
char	*executable(char *cmd, t_master *master)
{
	DIR		*ptr;
	char	*ret;

    if (access(cmd, F_OK) != 0)
    {
		print_error("minishell", cmd, "No such file or directory\n");
		clean_free(master, 127);
	}
    ptr = opendir(cmd);
	if (errno != 20) 
    {
		if (ptr)
			if (closedir(ptr) == -1)
                clean_free(master, 1);
        print_error("minishell", cmd, "is a directory\n");
		clean_free(master, 126);
    }
    if (access(cmd, X_OK) == 0)
	{
		ret = ft_strdup(cmd);
		if (!ret)
			clean_free(master, 1);
		return (ret);
	}
    print_error("minishell", cmd, "Permission denied\n");
    clean_free(master, 126);
	return (NULL);
}


/**
 * Checks if first arg starts with one or more '.' and it is followed by a '/'
*/
_Bool	is_path(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] && cmd[i] != '/')
		i++;
	if (!cmd[i])
		return (0);
	return (1);
}


_Bool	is_dots(char *cmd)
{
	if (ft_strlen(cmd) == 1 && *cmd == '.')
		return (1);
	else if (ft_strlen(cmd) == 2 && cmd[0] == '.' && cmd[1] == '.')
		return (1);
	return (0);
}


/**
 * Checks if the only path is 'bin/'
*/
_Bool	path_bin(char **path)
{
	if (!path || !*path)
		return (0);
	if (ft_strcmp(path[0], "/bin"))
		return (0);
	if (!path[1])
		return (1);
	return (0);
}

/**
 * Checks if path content is empty
 * Treats exception of whoami with PATH=":::::"
*/
_Bool	check_path(char **path, char *cmd, t_master *master)
{
	(void) master;
	(void) cmd;	
	if (*path)
		return (0);
	if (access(cmd, F_OK) != 0 && *getvar_value(master, "PATH"))
		return (0);
	return (1);
}

//Prueba en cada direccion de path si encuentra el comando necesario
//y lo devuelve en formato "/bin/ls"
char    *get_command(char **path, char *cmd, t_master *master)
{
    int 	i;
    char    *aux;
    char    *path_cmd;

    i = 0;
	if (!path || check_path(path, cmd, master) || is_path(cmd))
		return (executable(cmd, master));
	if (is_dots(cmd))
	{
		return (NULL);
	}
    while (path[i])
    {
        aux = ft_strjoin(path[i], "/");
		if(!aux)
		{
			free_double_array(path);
			clean_free(master, 1);
		}
        path_cmd = join_free(aux, cmd);
		if(!path_cmd)
		{
			free(aux);
			free_double_array(path);
			clean_free(master, 1);
		}
        if (access(path_cmd, F_OK) == 0)
		{
			if (access(path_cmd, X_OK) == 0)
				return (path_cmd);
			print_error("minishell", path_cmd, "Permission denied\n");
			free(path_cmd);
			if (path)
				free_double_array(path);
			clean_free(master, 126);
		}
        i++;
    }
	if (path_bin(path))
		return (executable(cmd, master));
	return (NULL);
}

//ejecuta los comandos en un child process
void exec_bin(t_master *master, t_command *cmd)
{
    char    **path;
    char    *command;
    char    **env;

	path = find_path(master);
	command = get_command(path, cmd->args_char[0], master);
	free_double_array(path);
    if (!command)
		exec_aux_free(cmd, master);
	path = copy_double_array(cmd->args_char);
	env = env_to_array(master->env);
	if (!path || !env)
		exec_aux_bin_free(command, path, env, master);
	clean_free_no_exit(master);
	execve(command, path, env);
	free_fail_exec(command, path, env);
}

void	exec_aux_bin_free(char *command, char**path, char **env, t_master *master)
{
	if (command)
		free(command);
	if (path)
		free_double_array(path);
	if (env)
		free_double_array(env);
	clean_free(master, 1);
	
}

int	exec_builtin(char *command, t_command *cmd, t_env *env, t_master *master)
{
  if (strcmp(command, "echo") == 0)
    return (ft_echo(cmd->args_char));
  else if (ft_strcmp(command, "cd") == 0)
		return (ft_cd(env, cmd->args_char));
  else if (ft_strcmp(command, "pwd") == 0)
		return (ft_pwd(env));
  else if (ft_strcmp(command, "export") == 0)
		return (ft_export(env, cmd->args_char, master));
	else if (ft_strcmp(command, "unset") == 0)
		return (ft_unset(env, cmd->args_char));
  else if (ft_strcmp(command, "env") == 0)
		return (ft_env(env));
  else if (ft_strcmp(command, "exit") == 0)
    return (ft_exit(cmd->args_char, master));
	return (0);
	
}

int is_builtin(char *command)
{
  if (strcmp(command, "echo") == 0)
    return (1);
  if (ft_strcmp(command, "pwd") == 0)
	  return (1);
  if (ft_strcmp(command, "env") == 0)
    return (1);
  if (ft_strcmp(command, "unset") == 0)
		return (1);
  if (ft_strcmp(command, "export") == 0)
		return (1);
  if (ft_strcmp(command, "cd") == 0)
		return (1);
  if (ft_strcmp(command, "exit") == 0)
    return (1);
  if(1)
		return (0);
  else
    return (0);
}

int exec(t_master *master, t_command *cmd)
{
	if (master->num_commands == 1)
    	exec_one(master, cmd);
	else if (!cmd->args_char[0])
		exit(0);
	else if (is_builtin(cmd->args_char[0]))
    exit(exec_builtin(cmd->args_char[0], cmd, master->env, master)); //@areview for leaks
	else
    	exec_bin(master, cmd);
  	return (0);
}