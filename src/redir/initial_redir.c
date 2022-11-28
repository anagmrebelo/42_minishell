/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:21:48 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/26 19:21:52 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	handle_outputs(cmd);
	if(cmd->inv_file)
	{
		close(master->fd[WRITE]);
		printf("minishell: %s: No such file or directory\n", last_token(cmd->inputs)->str);
		exit(1);//correct
	}
	redir_inputs(cmd);
	redir_outputs(cmd, master);
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
