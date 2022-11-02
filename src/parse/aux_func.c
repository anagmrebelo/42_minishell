#include "../../include/minishell.h"

void    print_list_tokens(t_token *list)
{
    int i;

    i = 0;
    while(list)
    {
        printf("%d: %s\n", i, list->str);
        list = list->next;
        i++;
    }
}