#include "../../include/minishell.h"

void    print_unset_error(char *str)
{
    ft_putstr_fd("minishell: unset: `", 2);
    ft_putstr_fd(str, 2);
    ft_putendl_fd("': not a valid identifier", 2);
}

int first_u_check(char *str)
{
    if (str[0] == '-')
    {
        ft_putstr_fd("minishell: unset: ", 2);
        ft_putchar_fd(str[0], 2);
        ft_putchar_fd(str[1], 2);
        ft_putendl_fd(": invalid option", 2);
        ft_putendl_fd("unset: usage: unset [-f] [-v] [-n] [name ...]", 2);
        return (1);
    }
    return (0);
}

void    unset_var(t_env *env, char *str)
{
    t_env   *next;

    while (env != NULL)
    {
        if (env->next != NULL && (ft_strcmp(env->next->title, str) == 0))
        {
            next = env->next->next;
            free_env(env->next);
            env->next = next;
        }
        env = env->next;
    }
}

int check_var(char *str)
{
    int len;
    int i;

    len = ft_strlen(str);
    i = 0;
    while (i < len)
    {
        if (!ft_isalpha(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int    ft_unset(t_env *env, char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (first_u_check(args[i]))
        {
            return (1);
            break ;
        }
        if(check_var(args[i]))
            unset_var(env, args[i]);
        else
        {
            print_unset_error(args[i]);
            return (1);
        }
        i++;
    }
    return (0);
}