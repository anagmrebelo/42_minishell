#include "../../include/minishell.h"

//CAMBIAR VALUE x title, si hay 2 variables con el mismo valor no sabremos cual hacer unset

void    ft_unset(t_env *env, char **args)
{
    t_env *next;
    //t_env *aux;

    //aux = env;
    while (env != NULL)
    {
        if (env->next != NULL && (ft_strcmp(env->next->title, args[1]) == 0))
        {
            next = env->next->next;
            free_env(env->next);
            env->next = next;
        }
        env = env->next;
    }
}