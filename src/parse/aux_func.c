#include "../../include/minishell.h"

void    print_list_tokens(t_token *list)
{
    int i;

    i = 0;
    while(list)
    {
        printf("%d: %s  -> type: %d\n", i, list->str, list->type);
        list = list->next;
        i++;
    }
}