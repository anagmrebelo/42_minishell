#include "../../include/minishell.h"

void    create_shlvl(t_env *env)
{
    t_env   *new;
    char    *title;
    char    *value;

    title = ft_strdup("SHLVL");
    value = ft_strdup("1");
    new = new_env(title, value);
    add_back(env, new);
}

void    create_usr_bin(t_env *env)
{
    t_env   *new;
    char    *title;
    char    *value;

    title = ft_strdup("_");
    value = ft_strdup("usr/bin/env");
    new = new_env(title, value);
    add_back(env, new);
}

void    create_path(t_env *env)
{
    t_env   *new;
    char    *title;
    char    *value;

    title = ft_strdup("PATH");
    value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
    new = new_env(title, value);
    add_back(env, new);
}

int    default_env(t_master *master)
{
    t_env   *env;
    char *pwd;

    env = ft_calloc(1, sizeof(t_env));
    if (!env)
        clean_free(master, 1);
    master->env = env;
    pwd = malloc(4097 * sizeof(char));
    if (!pwd)
        return (1);
    if (getcwd(pwd, 4097) == NULL)
        return (1);
    env->title = ft_strdup("PWD");
    env->value = ft_strdup(pwd);
    create_shlvl(env);
    create_usr_bin(env);
    create_path(env);
    return (0);
}