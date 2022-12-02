#include "../../include/minishell.h"

/**
 * Function that deletes token from list and updates next and prev
*/
void    delete_token(t_token *token, t_master *master)
{
    if(token->prev)
        token->prev->next = token->next;
    else
        master->token_list = token->next;
    if(token->next)
        token->next->prev = token->prev;
    if(token->str)
        free(token->str);   //CAN BE PROBLEMATIC; MAKE SURE IF IT WAS EMPTIED WE CHANGED TO NULL;
}

/**
 * Deletes tokens that have an empty str
*/
void	clean_tokens(t_master *master)
{
	t_token	*temp;

	temp = master->token_list;
	while (temp)
	{
		if (!temp->str || !temp->str[0])
			delete_token(temp, master);
		temp = temp->next;
	}
}
