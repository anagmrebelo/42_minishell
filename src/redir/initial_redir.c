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
}

/**
 * Creates and clears output files if necessary
 * If there is an invalid input file, next steps won't be processed
 * Sets STDOUT to either default, pipe or token from cmd->outputs
 * Sets STDIN to either default, pipe or token from cmd->inputs
*/
_Bool	handle_redirs(t_command *cmd, t_master *master)
{
	int	fd_input;
	int	fd_output;

	handle_outputs(cmd, master);
	if(cmd->inv_file)
		return (0);
	close(master->fd[WRITE]);
	fd_input = input_func(cmd, master);
	dup2(fd_input, STDIN_FILENO);
	close(fd_input);
	close(master->fd[READ]);
	if(pipe(master->fd) == -1)
		printf("Error or creating pipe - function init redirs\n");	// Change to exit program
	fd_output = output_func(cmd, master);
	dup2(fd_output, STDIN_FILENO);
	close(fd_output);
	return (1);
}

int	input_func(t_command *cmd, t_master *master)
{
	if (cmd->inputs)
		printf("FD_INPUT: %s\n", last_token(cmd->inputs)->str);
	else if(cmd->cmd_nb != 1)
		printf("FD_INPUT: PIPE\n");
	else
		printf("FD_INPUT: STDIN_FILENO\n");
	return (dup(master->std_in));
}

int	output_func(t_command *cmd, t_master *master)
{
	if (cmd->outputs)
		printf("FD_OUTPUT: %s\n", last_token(cmd->outputs)->str);
	else if(cmd->cmd_nb != master->numCommands)
		printf("FD_OUTPUT: PIPE\n");
	else
		printf("FD_OUTPUT: STDOUT_FILENO\n");
	return (dup(master->std_out));
}
