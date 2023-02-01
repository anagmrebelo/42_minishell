#include "../../include/minishell.h"

void    print_export_error(char *str)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(str, 2);
    ft_putendl_fd("': not a valid identifier", 2);
}

void    add_to_env(char *title, char *value, t_env *env)
{
    t_env   *new;

    new = new_env(title, value);
    add_back(env, new);
}

void    update_var(t_env *env, char *title, char *str, t_master *master)
{
    while (env != NULL)
    {
        if (ft_strcmp(title, env->title) == 0)
        {
            env->value = get_value(str, master);
            break ;
        }
        env = env->next;
    }
}

int equal_check(char *str)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str);
    while (i < len)
    {
        if (str[i] == '=')
            i++;
        else
            return (0);
    }
    return (1);
}

int first_check(char *str)
{
    if (str[0] == '-')
    {
        ft_putstr_fd("minishell: export: ", 2);
        ft_putchar_fd(str[0], 2);
        ft_putchar_fd(str[1], 2);
        ft_putendl_fd(": invalid option", 2);
        ft_putendl_fd("export: usage: export [-fn] [name[=value] ...] or export -p", 2);
        return (1);
    }
    return (0);
}

int var_title_check(char *str)
{
    int i;
    int len;
    char    *aux;

    aux = ft_strchr(str, '=');
	if (!aux)
		len = ft_strlen(str);
	else
		len = aux - str;
    if (len == 0)
        return (0);
    if (equal_check(str))
        return (0);
    if (ft_isalpha(str[0]) || str[0] == '_')
    {
        i = 1;
        while (i < len)
        {
            if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
            {
                if ((i == (len - 1)) && str[i] == '+')
                    return (1);
                return (0);
            }
            else
                i++;
        }
    }
    else
        return (0);
    return (1);
}

int ft_export(t_env *env, char **args, t_master *master)
{
    int i;
    int ret;
    char    *title;

    ret = 0;
    if (!args[1])
    {
        if (!find_in_env(env, "OLDPWD"))
            add_to_env(ft_strdup("OLDPWD"), NULL, env);
        print_sort_env(env);
        return (0);
    }
    else
    {
        i = 1;
        while (args && args[i])
        {
            if (first_check(args[i]))
            {
                ret = 2;
                break ;
            }
            if(var_title_check(args[i]))
            {
                title = get_title(args[i], master);
                if (find_in_env(env, title))
                {
                    update_var(env, title, args[i], master);
                    free (title);
                }
                else
                    add_to_env(title, get_value(args[i], master), env);
            }
            else
            {
                print_export_error(args[i]);
                ret = 1;
            }
            i++;
        }
    }
    return (ret);
}