
#include "../../include/minishell.h"
    
void    prep_next_line(t_master *master)
{
	reset_redirs(master);
    free_token_list(master->token_list);
	master->token_list = NULL;
	free_commands(master);
}

void	reset_redirs(t_master *master)
{
	(void) master;
}
