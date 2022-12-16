#include "../../include/minishell.h"

// t_env   *realloc_env(t_env *env)
// {
//     t_env   *realloc_env;
//     t_env   *new;
//     t_env   *aux;

//     aux = env;
//     realloc_env = ft_calloc(1, sizeof(t_env));
//     realloc_env->content = ft_strdup(aux->content);
//     realloc_env->title = ft_strdup(aux->title);
// 	realloc_env->value = ft_strdup(aux->value);
// 	realloc_env->next = NULL;
//     aux = env->next;
//     while (aux != NULL)
// 	{
// 		new = new_env(aux->content, ft_strdup(aux->title), ft_strdup(aux->value));
// 		add_back(realloc_env, new);
// 		aux = aux->next;
// 	}
//     return (realloc_env);
// }

//CAMBIAR VALUE x title, si hay 2 variables con el mismo valor no sabremos cual hacer unset

void    ft_unset(t_env *env, char **args)
{
    t_env *next;
    //t_env *aux;

    //aux = env;
    while (env != NULL)
    {
        if (env->next != NULL && (ft_strcmp(env->next->value, args[1]) == 0))
        {
            next = env->next->next;
            free_env(env->next);
            env->next = next;
        }
        env = env->next;
    }
    //env = realloc_env(aux);
}