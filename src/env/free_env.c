#include "minishell.h"

void    free_env(t_env *item)
{
    if (item)
    {
        free(item->content);
        free(item->title);
        free(item->value);
        free(item);
    } 
}

void    free_env_lst(t_env *list)
{
    t_env *tmp;

    while(list)
    {
        tmp = list->next;
        free_env(list);
        list = tmp;
    }
}