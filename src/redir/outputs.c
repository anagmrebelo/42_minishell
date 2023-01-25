/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:21:41 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/25 03:25:19 by arebelo          ###   ########.fr       */
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
				clean_free(master, 1);
			if (close(temp->fd) == -1)
				clean_free(master, 1);
		}
		else
		{
			temp->fd = open(temp->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (temp->fd == -1)
				clean_free(master, 1);
			if (close(temp->fd) == -1)
				clean_free(master, 1);
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
			if (close(last_token(cmd->outputs)->fd) == -1)
				clean_free(master, 1);
		}
		else
			clean_free(master, 1);
	}
}
