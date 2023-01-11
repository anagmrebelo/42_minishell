#include "../../include/minishell.h"

int change_dir(char *arg, char *oldpwd, t_env *env)
{
    if (chdir(arg) == 0)
    {
        update_env(oldpwd, env);
        return (0);
    }
    else
    {
        ft_putstr_fd("cd: ", 1);
        ft_putstr_fd(arg, 1);
        ft_putstr_fd(": ", 1);
        if (access(arg, F_OK) == -1)
            ft_putendl_fd("No such file or directory", 1);
        else if (access(arg, R_OK) == -1)
            ft_putendl_fd("Permission denied", 1);
        else
            ft_putendl_fd("Not a directory", 1);
        return (1);
    }
}

void    update_oldpwd(char *oldpwd, t_env *env)
{
    while (env != NULL)
    {
        if (ft_strcmp("OLDPWD", env->title) == 0)
        {
            free (env->value);
            env->value = ft_strdup(oldpwd);
            break ;
        }
        else
            env = env->next;
    }
}

void    update_pwd(t_env *env)
{
    char    *pwd;

    pwd = malloc(4097 * sizeof(char));
    if (!pwd)
        return (1);
    if (getcwd(pwd, 4097) == NULL)
        return (1);
    while (env != NULL)
    {
        if (ft_strcmp("PWD", env->title) == 0)
        {
            free (env->value);
            env->value = ft_strdup(pwd);
            break ;
        }
        else
            env = env->next;
    }
    free (pwd);
}

void    update_env(char *oldpwd, t_env *env)
{
    update_oldpwd(oldpwd, env);
    update_pwd(env);
}

char    *get_env_value(char *title, t_env *env)
{
    while (env != NULL)
    {
        if (ft_strcmp(title, env->title) == 0)
            return (env->value);
        else
            env = env->next;
    }
    return (NULL);
}

int ft_cd(t_env *env, char **args)
{
    char    *home_path;
    char    *pwd;
    int     i;

    home_path = get_env_value("HOME", env);
    pwd = malloc(4097 * sizeof(char));
    if (!pwd)
        return (1);
    if (getcwd(pwd, 4097) == NULL)
        return (1);
    if (args[1] == NULL || ft_strcmp(args[1], "~") == 0 
        || ft_strcmp(args[1], "--") == 0)
        i = change_dir(home_path, pwd, env);
    else if (strcmp(args[1], "-") == 0)
    {
        if (!change_dir(home_path, pwd, env))
        {
            ft_putendl_fd(home_path, 1);
            i = 0;
        }
        else
            i = 1;
    }
    else
        i = change_dir(args[1], pwd, env);
    free (pwd);
    return (i);
}