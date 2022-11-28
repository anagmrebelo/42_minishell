/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:18:50 by mrollo            #+#    #+#             */
/*   Updated: 2022/11/25 20:14:07 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Toma la variable $PATH y la separa (con split)

char    **find_path(t_master *master)
{
    char **path;
    t_env *tmp;
    //int i;

    path = NULL;
    tmp = master->env;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->title, "PATH") == 0)
        {
            path = ft_split(tmp->value, ':');
            break;
        }
        tmp = tmp->next;
    }
    //imprimir path
    // i = 0;
    // while (path[i])
    // {
    //     printf("path[%d]: %s\n", i, path[i]);
    //     i++;
    // }
    return (path);
}


//Prueba en cada direccion de path si encuentra el comando necesario
//y lo devuelve en formato "/bin/ls"

char    *get_command(char **path, char *cmd)
{
    int i;
    char    *aux;
    char    *path_cmd;

    i = 0;
    while (path[i])
    {
        aux = ft_strjoin(path[i], "/");
        path_cmd = join_free(aux, cmd);
        //printf("probando: %s\n", path_cmd);
        if (access(path_cmd, 0) == 0)
            return (path_cmd);
        i++;
    }
    return (NULL);
}

//convierte token list en array para pasarlo a execve

char    **token_to_array(t_token *token)
{
    char    **token_array;
    t_token *aux;
    int len;
    int i;

    aux = token;
    len = 0;
    while (aux != NULL)
    {
        len++;
        aux = aux->next;
    }
    //len = env_len(env);
    token_array = (char **)ft_calloc((len + 1), sizeof(char *));
    if (!token_array)
        return (NULL);
    i = 0;
    while (i < len)
    {
        token_array[i] = ft_strdup(token->str);
        token = token->next;
        i++;
    }
    //print_array(array_env, len);
    return (token_array);
}

//ejecuta los comandos en un child process

void exec_bin(t_master *master, t_command *cmd)
{
    char    **path;
    char    *command;
    char    **env;

	path = find_path(master);
	command = get_command(path, cmd->args_char[0]);
	env = env_to_array(master->env);

	execve(command, cmd->args_char, env);	
	exit(1);// Adjust
}

int is_builtin(char *command)
{
	if(1)
		return (0);
    if (strcmp(command, "echo") == 0)
		return (1);
    if (ft_strcmp(command, "cd") == 0)
		return (1);
    if (ft_strcmp(command, "pwd") == 0)
		return (1);
    if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
    if (ft_strcmp(command, "env") == 0)
        return (1);
    if (ft_strcmp(command, "exit") == 0)
        return (1);
    else
        return (0);
}

int exec(t_master *master, t_command *cmd)
{
    if (is_builtin(cmd->args_char[0]))
        print_list_tokens(cmd->args);
    else if (master->numCommands == 1)
        exec_one(master, cmd);
    else
        exec_bin(master, cmd);
    return (0);
}