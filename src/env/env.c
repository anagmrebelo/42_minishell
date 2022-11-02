#include "minishell.h"

void    free_array(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
    {
        free (array[i]);
        i++;
    }
    free(array);
}

void    print_array(char **array, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        printf("%s\n", array[i]);
        i++;
    }
}

int env_len(t_env *env)
{
    t_env   *tmp;
    int i;

    i = 0;
    tmp = env;
    while (tmp != NULL)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

char    **env_to_array(t_env *env)
{
    char    **array_env;
    int len;
    int i;

    len = env_len(env);
    array_env = (char **)ft_calloc((len + 1), sizeof(char *));
    if (!array_env)
        return (NULL);
    i = 0;
    while (i < len)
    {
        array_env[i] = ft_strdup(env->content);
        env = env->next;
        i++;
    }
    //print_array(array_env, len);
    return (array_env);
}