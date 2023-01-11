#include "../../include/minishell.h"

void    ft_unset(t_env *env, char **args)
{
    t_env *next;

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