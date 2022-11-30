#include "../../include/minishell.h"

void    print_echo(char *str, int fd)
{
    ft_putstr_fd(str, fd);
}

int ft_echo(char **args)
{
    int i;
    int flag;

    args = &args[1];
    flag = 0;
    if (!args[0])
    {
        ft_putchar_fd('\n', STDIN_FILENO);
        return (0);
    }
    if (args[0][0] == '-' && args[0][1] == 'n' && args[0][2] == '\0')
    {
        flag = 1;
        args = &args[1];
    }
    i = 0;
    while(args[i])
    {
        print_echo(args[i], STDIN_FILENO);
        if (args[i + 1])
            ft_putchar_fd(' ', STDIN_FILENO);
        i++;
    }
    if (!args[i] && !flag)
        ft_putchar_fd('\n', STDIN_FILENO);
    return (0);
}