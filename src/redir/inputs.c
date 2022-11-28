/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:57:59 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/28 15:54:29 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function that makes the STDIN be the last input of the command
 * In the case of no redirections the STDIN was set before to PIPE or default STDIN
*/
void	redir_inputs(t_command *cmd)
{
	if(cmd->inputs)
		{
			last_token(cmd->inputs)->fd = open(last_token(cmd->inputs)->str, O_RDONLY);
			if (last_token(cmd->inputs)->fd != -1)
			{
				dup2(last_token(cmd->inputs)->fd, STDIN_FILENO);
				close(last_token(cmd->inputs)->fd);
			}
			else
				exit(1); //handle error
		}
}

/**
 * Function that evaluates if path to a file is valid
*/
_Bool	validate_file(char *path)
{
	if(access(path, R_OK) == 0)
		return (1);
	return (0);
}