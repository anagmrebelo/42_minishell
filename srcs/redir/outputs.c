/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:21:41 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 14:55:26 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/**
  * If str contains a '/'
  * then it confirms if path treats a document as a directory
  * if there is no permissions to access to directory
  * if path is not valid as does not exist such a file or dir
 */
static _Bool	check_path_tofile(char *str, t_command *cmd, t_master *master)
{
	char	*tmp;

	tmp = file_new_path(str, master);
	opendir(tmp);
	if (errno == ENOTDIR)
	cmd->not_dir = 1;
	else if (!access(tmp, W_OK))
	{
		free(tmp);
		return (1);
	}
	else if (!access(tmp, F_OK))
		cmd->inv_perm = 1;
	else
		cmd->inv_file = 1;
	cmd->failed = cmd->outputs;
	free(tmp);
	return (0);
}

/**
 * Checks if path to file exists, if not creates file
 * If type = OUTPUT clears content
 * Closes all files
*/
void	handle_outputs(t_command *cmd, t_master *master)
{
	t_token	*temp;

	temp = cmd->outputs;
	while (temp && temp != last_token(cmd->failed))
	{
		if (temp->type == APPEND)
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
 * In the case of no explicit redirs, 
 * the STDOUT is directed to PIPE (if applicable) 
 * or it is maintained with default STDOUT
*/
void	redir_outputs(t_command *cmd, t_master *master)
{
	int	flag;
	int	temp;

	flag = O_WRONLY;
	if (cmd->outputs)
	{
		if (last_token(cmd->outputs)->type == APPEND)
			flag = O_APPEND;
		temp = open((last_token(cmd->outputs))->str, O_WRONLY | flag);
		(last_token(cmd->outputs))->fd = temp;
		if (last_token(cmd->outputs)->fd != -1)
		{
			if (dup2(last_token(cmd->outputs)->fd, STDOUT_FILENO) == -1)
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

_Bool	validate_output(char *str, t_command *cmd, t_master *master)
{
	if (!access(str, W_OK))
		return (1);
	if (!ft_strchr(str, '/'))
	{
		if (access(str, F_OK))
			return (1);
		cmd->inv_perm = 1;
		cmd->failed = cmd->outputs;
		return (0);
	}
	else
		return (check_path_tofile(str, cmd, master));
	return (1);
}

/**
 * Returns a malloc of str without the last part of path
 * (e.g. if str = src/parse/main.c returns src/parse)
*/
char	*file_new_path(char *str, t_master *master)
{
	int		i;
	char	*tmp;

	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == '/')
		{
			tmp = ft_substr(str, 0, i);
			if (!tmp)
				clean_free(master, 1);
			return (tmp);
		}
		i--;
	}
	return (NULL);
}
