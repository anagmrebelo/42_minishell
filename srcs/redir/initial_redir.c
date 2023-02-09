/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:21:48 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:48:28 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

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
 * Creates and clears output files if necessary
 * If there is an invalid input file, next steps won't be processed
 * Sets STDOUT to either default, pipe or token from cmd->outputs
 * Sets STDIN to either default, pipe or token from cmd->inputs
*/
void	handle_redirs(t_command *cmd, t_master *master)
{	
	if (cmd->inv_file)
		no_file_dir(master, (last_token(cmd->failed))->str, 1);
	if (cmd->inv_perm)
		perm_denied(master, (last_token(cmd->failed))->str, 1);
	if (cmd->not_dir)
		not_dir(master, (last_token(cmd->failed))->str, 1);
	redir_outputs(cmd, master);
	redir_inputs(cmd, master);
}

/**
 * Closes file descriptors initially saved with dup 
*/
void	close_init_redirs(t_master *master)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (master->std_in != -1)
		i = close(master->std_in);
	if (master->std_out != -1)
		j = close(master->std_out);
	if (i == -1 || j == -1)
	{
		free_master(master);
		exit(1);
	}
}

void	reset_redirs(t_master *master)
{
	if (dup2(master->std_in, STDIN_FILENO) == -1)
		clean_free(master, 1);
	if (dup2(master->std_out, STDOUT_FILENO) == -1)
		clean_free(master, 1);
}
