#include "minishell.h"

void    free_env(t_env *item)
{
    if (item)
    {
        //if(item->content)
            free(item->content);
        //iterm->content = NULL;
         //if(item->title)
            free(item->title);
        //iterm->title = NULL;
        //if(item->value)
            free(item->value);
        //iterm->value = NULL;
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