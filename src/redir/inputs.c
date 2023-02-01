/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:57:59 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/01 19:22:44 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function that makes the STDIN be the last input of the command
 * In the case of no redirections the STDIN was set before to PIPE
 * or default STDIN
*/
void	redir_inputs(t_command *cmd, t_master *master)
{
	int	temp;

	if (cmd->inputs)
	{
		temp = open((last_token(cmd->inputs))->str, O_RDONLY);
		(last_token(cmd->inputs))->fd = temp;
		if (last_token(cmd->inputs)->fd == -1)
			clean_free(master, 1);
		if (dup2(last_token(cmd->inputs)->fd, STDIN_FILENO) == -1)
		{
			close(last_token(cmd->inputs)->fd);
			clean_free(master, 1);
		}
		if (close(last_token(cmd->inputs)->fd) == -1)
			clean_free(master, 1);
	}		
}

/**
 * Function that evaluates if path to a file is valid and user has permissions
*/
_Bool	validate_input(t_token *temp, t_command *cmd)
{
	char	*path;

	path = temp->str;
	if (!access(path, R_OK))
		return (1);
	cmd->failed = cmd->inputs;
	if (!access(path, F_OK))
		cmd->inv_perm = 1;
	else
		cmd->inv_file = 1;
	return (0);
}
