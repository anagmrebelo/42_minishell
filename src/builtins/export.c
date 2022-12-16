#include "../../include/minishell.h"

void    add_to_env(char *content, char *title, char *value, t_env *env)
{
    t_env   *new;

    new = new_env(content, title, value);
    add_back(env, new);
}

char    *get_var_value(char *str)
{
    char    *aux;
    int     len;
    char    *value;

    aux = ft_strchr(str, '=');
    if (!aux)
        return (NULL);
    len = (aux - str) + 1;
    value = ft_substr(str, len, ft_strlen(str) - len);
    return (value);
}

char    *get_var_title(char *str)
{
    int     i;
    int     len;
    char    *aux;
    char    *title;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == '=')
        {
            aux = ft_strchr(str, '=');
            len = aux - str;
            title = ft_substr(str, 0, len);
            return (title);
        }
        else
            i++;
    }
    return (str);
}

int var_title_check(char *str)
{
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    return (1);
}

int ft_export(t_env *env, char **args)
{
    int i;

    //printf("args[0]: %s\nargs[1]: %s\nargs[2]: %s\n", args[0], args[1], args[2]);
    if (!args[1])
    {
        printf("hola\n");
        print_sort_env(env);
        return (0);
    }
    else
    {
        i = 1;
        while (args && args[i])
        {
            if(var_title_check(args[i]))
            {
                printf("ok\n");
                //printf("title: %s\n", get_var_title(args[i]));
                //printf("value: %s\n", get_var_value(args[i]));
                add_to_env(args[i], get_var_title(args[i]), get_var_value(args[i]), env);
            }
            else
                printf("not a valid identifier\n");
            i++;
        }
    }
    return (0);
}