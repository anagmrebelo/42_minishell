#include "../../include/minishell.h"

void    env_path_update(t_env *env, char *str)
{
    while (env != NULL)
    {
        if (strcmp(env->title, "PWD") == 0)
        {
            free (env->value);
            env->value = ft_strdup(str);
            break ;
        }
        env = env->next;
    }
}

int ft_pwd(t_env *env)
{
    char *pwd;

    pwd = malloc(4097 * sizeof(char));
    if (!pwd)
    {
        printf("calloc error\n");
        return (1);
    }
    if (getcwd(pwd, 4097) == NULL)
    {
        printf("error getcwd\n");
        return (1);
    }
    else
    {
        ft_putendl_fd(pwd, 1);
        env_path_update(env, pwd);
        free (pwd);
    }
    return (0);
}