#include "../../include/minishell.h"

void    print_list_tokens(t_token *list)
{
    while(list)
    {
        printf("%s\n", list->str);
        list = list->next;
    }
}