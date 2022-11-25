#include "../../include/minishell.h"

void	close_init_redirs(t_master *master)
{
	close(master->std_in);
	close(master->std_out);
}