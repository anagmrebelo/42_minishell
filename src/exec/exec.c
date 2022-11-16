/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:18:50 by mrollo            #+#    #+#             */
/*   Updated: 2022/11/08 12:18:58 by mrollo           ###   ########.fr       */
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

int exec_bin(t_master *master)
{
    char    **path;
    char    **str;
    char    *command;
    char    **env;
    pid_t   pid;

    pid = fork();
    if (pid < 0)
        printf("error pid\n");
    if (pid == 0)
    {
        str = token_to_array(master->token_list);
	    path = find_path(master);
	    command = get_command(path, master->token_list->str);
	    env = env_to_array(master->env);
        if (execve(command, str, env) == -1)
            printf("error execve\n");
    }
    else
        waitpid(pid, NULL, 0); //cambiar NULL x global
    return (0);
}

int is_builtin(char *command)
{
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

int exec(t_master *master)
{
    if (is_builtin(master->token_list->str))
        print_list_tokens(master->token_list);
    else
        exec_bin(master);
    return (0);
}