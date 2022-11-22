#include "../../include/minishell.h"

void	close_init_redirs(t_master *master)
{
	close(master->std_in);
	close(master->std_out);
}

void	adjust_redirs(t_command *cmd, t_master *master)
{
	close(master->fd[WRITE]);
	close(master->fd[READ]);
	(void) cmd;
}