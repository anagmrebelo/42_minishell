#include "../../include/minishell.h"

void    print_exit_error(int n, char *str)
{
    if (n == 1)
    {
        ft_putendl_fd("exit", 2);
        ft_putendl_fd("minishell: exit: too many arguments", 2);
    }
    if (n == 2)
    {
        ft_putendl_fd("exit", 2);
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd("numeric argument required", 2);
    }
}

 int    is_numeric(char *str)
 {
    size_t  i;
    size_t  len;

    len = ft_strlen(str);
    if (len == 1)
    {
        if (ft_isdigit(str[0]))
            return (0);
        else
            return (1);
    }
    i = 1;
    while (str[i])
    {
        if (str[0] == '-' || str[0] == '+' || ft_isdigit(str[0]))
        {
            if (ft_isdigit(str[i]))
                i++;
            else
                return (1);
        }
        else
            return (1);
    }
    return (0);
 }

int aux_exit(char **args, t_master *master)
{
    int n;

    if (is_numeric(args[1]))
    {
        print_exit_error(2, args[1]);
        master->status = 1;
        n = 255;
    }
    if (!is_numeric(args[1]) && !args[2])
    {
        n = ft_atoi(args[1]);
        ft_putendl_fd("exit", 2);
        master->status = 1;
    }
    return (n);
}

int ft_exit(char **args, t_master *master)
{
    if (!args[1])
    {
        ft_putendl_fd("exit", 2);
        master->status = 1;
    }
    else if (args[2] && !is_numeric(args[1]))
    {
        print_exit_error(1, NULL);
        return (1);
    }
    else if (args[1])
        return (aux_exit(args, master));
    return (0);
}