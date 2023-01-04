/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:21:48 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/04 15:25:40 by anarebelo        ###   ########.fr       */
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
	if (master->std_in == -1 || master->std_out == -1)
		clean_free(master, errno);
}

/**
 * Create pipe and exit if error
*/
void	init_pipe(t_master *master)
{
	if(pipe(master->fd) == -1)
		clean_free(master, 1);
	close(master->fd[WRITE]);
}

/**
 * Creates and clears output files if necessary
 * If there is an invalid input file, next steps won't be processed
 * Sets STDOUT to either default, pipe or token from cmd->outputs
 * Sets STDIN to either default, pipe or token from cmd->inputs
*/
void	handle_redirs(t_command *cmd, t_master *master)
{	
	close(master->fd[READ]);
	if(cmd->inv_file)
	{
		print_error("minishell", last_token(cmd->inputs)->str, "No such file or directory\n", 2);
		close(master->fd[WRITE]);
		clean_free(master, 2);
	}
	redir_outputs(cmd, master);
	redir_inputs(cmd, master);
}

void	handle_pipe(t_master *master, t_command *cmd)
{
	if (cmd->cmd_nb != 1)
		if(dup2(master->fd[READ], STDIN_FILENO) == -1)
			clean_free_pipe_read(master, 1);
	close(master->fd[READ]);
	if(pipe(master->fd) == -1)
		clean_free(master, 1);
	return ;
}
