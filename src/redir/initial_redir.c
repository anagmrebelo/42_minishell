#include "../../include/minishell.h"

/**
 * Copies the initial STDIN and STDOUT to the master structure
 * Used to restore STDIN and STDOUT after each line is executed
*/
void	init_redirs(t_master *master)
{
	master->std_in = dup(STDIN_FILENO);
	master->std_out = dup(STDOUT_FILENO);
	if(pipe(master->fd) == -1)
		printf("Error or creating pipe - function init redirs\n");	// Change to exit program
	close(master->fd[WRITE]);
}

/**
 * Creates and clears output files if necessary
 * If there is an invalid input file, next steps won't be processed
 * Sets STDOUT to either default, pipe or token from cmd->outputs
 * Sets STDIN to either default, pipe or token from cmd->inputs
*/
_Bool	handle_redirs(t_command *cmd, t_master *master)
{	
	close(master->fd[READ]);
	handle_outputs(cmd, master);
	if(cmd->inv_file)
	{
		close(master->fd[WRITE]);
		exit(1);//correct
	}
	if(cmd->inputs)
	{
		dup2(last_token(cmd->inputs)->fd, STDIN_FILENO);
		close(last_token(cmd->inputs)->fd);
	}
	if(cmd->cmd_nb != master->numCommands)
		dup2(master->fd[WRITE], STDOUT_FILENO);
	close(master->fd[WRITE]);
	return (1);
}

void	handle_pipe(t_master *master, t_command *cmd)
{
	if (cmd->cmd_nb != 1)
		dup2(master->fd[READ], STDIN_FILENO);
	close(master->fd[READ]);
	pipe(master->fd);
	return ;
}

void    prep_next_line(t_master *master)
{
	close(master->fd[READ]);
	dup2(master->std_in, STDIN_FILENO);
    free_token_list(master->token_list);
	master->token_list = NULL;
	free_commands(master);
	close_init_redirs(master);
}
