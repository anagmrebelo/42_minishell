/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:21:41 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/04 15:26:29 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 * Checks if path to file exists, if not creates file
 * If type = OUTPUT clears content
 * Closes all files
*/
void	handle_outputs(t_command *cmd, t_master *master)
{
	t_token	*temp;

	temp = cmd->outputs;
	while(temp)
	{
		if(temp->type == APPEND)
		{
			temp->fd = open(temp->str, O_WRONLY | O_CREAT, 0644);
			if (temp->fd == -1)
				clean_free_pipe_read(master, 1);
			close(temp->fd);
		}
		else
		{
			temp->fd = open(temp->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (temp->fd == -1)
				clean_free_pipe_read(master, 1);
			close(temp->fd);
		}
		temp = temp->next;
	}
}

/**
 * Function that makes STDOUT be the last output of the command
 * In the case of no explicit redirs, the STDOUT is directed to PIPE (if applicable) or it is maintained with default STDOUT
*/
void	redir_outputs(t_command *cmd, t_master *master)
{
	int	flag;

	flag = O_WRONLY;
	if (cmd->outputs)
	{
		if(cmd->cmd_nb != master->numCommands) //@arebelo review condition
			close(master->fd[WRITE]);
		if(last_token(cmd->outputs)->type == APPEND)
			flag = O_APPEND;
		last_token(cmd->outputs)->fd = open(last_token(cmd->outputs)->str, O_WRONLY | flag);
		if (last_token(cmd->outputs)->fd != -1)
		{
			if(dup2(last_token(cmd->outputs)->fd, STDOUT_FILENO) == -1)
			{
				close(last_token(cmd->outputs)->fd);
				clean_free(master, 1);
			}
			close(last_token(cmd->outputs)->fd);
		}
		else
			clean_free(master, 1);
	}
	else if(cmd->cmd_nb != master->numCommands)
	{
		if (dup2(master->fd[WRITE], STDOUT_FILENO) == -1)
		{
			close(master->fd[WRITE]);
			clean_free(master, 1);
		}
		close(master->fd[WRITE]);
	}	
}
