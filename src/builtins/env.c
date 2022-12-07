#include "../../include/minishell.h"

void    ft_env(t_env *env)
{
    while (env != NULL)
    {
        ft_putstr_fd(env->title, 1);
        ft_putchar_fd('=', 1);
        ft_putendl_fd(env->value, 1);
        env = env->next;
    }
}