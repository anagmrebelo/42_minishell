#include "../../include/minishell.h"

void    print_export_error(char *str)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(str, 2);
    ft_putendl_fd("': not a valid identifier", 2);
}

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

void    update_var(t_env *env, char *str)
{
    char    *end;
    size_t  n;

    end = ft_strchr(str, '=');
    if (!end)
        n = ft_strlen(str);
    else
        n = end - str;
    while (env != NULL)
    {
        if (ft_strncmp(env->title, str, n) == 0)
        {
            env->value = get_var_value(str);
            break ;
        }
        env = env->next;
    }
}

int var_exist(t_env *env, char *str)
{
    char    *end;
    size_t  n;

    end = ft_strchr(str, '=');
    if (!end)
        n = ft_strlen(str);
    else
        n = end - str;
    while (env != NULL)
    {
        if (ft_strncmp(env->title, str, n) == 0)
            return (1);
        env = env->next;
    }
    return (0);
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
                if (var_exist(env, args[i]))
                    update_var(env, args[i]);
                else
                    add_to_env(args[i], get_var_title(args[i]), get_var_value(args[i]), env);
            }
            else
                print_export_error(args[i]);
            i++;
        }
    }
    return (0);
}