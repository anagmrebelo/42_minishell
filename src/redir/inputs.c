/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:57:59 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/30 16:08:39 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function that makes the STDIN be the last input of the command
 * In the case of no redirections the STDIN was set before to PIPE or default STDIN
*/
void	redir_inputs(t_command *cmd, t_master *master)
{
	if(cmd->inputs)
	{
		last_token(cmd->inputs)->fd = open(last_token(cmd->inputs)->str, O_RDONLY);
		if (last_token(cmd->inputs)->fd == -1)
			clean_free(master);
		if (dup2(last_token(cmd->inputs)->fd, STDIN_FILENO) == -1)
		{
			close(last_token(cmd->inputs)->fd);
			clean_free(master);
		}
		close(last_token(cmd->inputs)->fd);
	}		
}

/**
 * Function that evaluates if path to a file is valid
*/
_Bool	validate_file(char *path, t_master *master)
{
	int	status;

	status = access(path, R_OK);
	if (status == 0)
		return (1);
	return (0);
	(void) master;
}