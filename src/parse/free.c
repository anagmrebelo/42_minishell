
#include "../../include/minishell.h"
    
void    prep_next_line(t_master *master)
{
    free_token_list(master->token_list);
	master->token_list = NULL;
	free_commands(master);
	close_init_redirs(master);
	dup2(master->std_in, STDIN_FILENO);
}