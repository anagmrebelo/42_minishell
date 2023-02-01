/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:51:35 by anarebelo         #+#    #+#             */
/*   Updated: 2023/02/01 11:51:44 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Looks for variable path and transforms its paths into char**
*/
char	**find_path(t_master *master)
{
	char	**path;
	t_env	*tmp;

	path = NULL;
	tmp = master->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->title, "PATH") == 0)
		{
			path = ft_split(tmp->value, ':');
			if (!path)
				clean_free(master, 1);
			break ;
		}
		tmp = tmp->next;
	}
	return (path);
}

/**
 * Checks if first arg starts with one or more '.' and it is followed by a '/'
*/
_Bool	is_path(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] && cmd[i] != '/')
		i++;
	if (!cmd[i])
		return (0);
	return (1);
}

/**
 * Checks if the only path is 'bin/'
*/
_Bool	path_bin(char **path)
{
	if (!path || !*path)
		return (0);
	if (ft_strcmp(path[0], "/bin"))
		return (0);
	if (!path[1])
		return (1);
	return (0);
}

/**
 * Checks if path content is empty
 * Treats exception of whoami with PATH=":::::"
*/
_Bool	check_path(char **path, char *cmd, t_master *master)
{
	if (*path)
		return (0);
	if (access(cmd, F_OK) != 0 && *getvar_value(master, "PATH"))
		return (0);
	return (1);
}

/**
 * Checks if it can't find the file, if it is a directory
 * and if it has the correct permissions to execute
*/
char	*executable(char *cmd, t_master *master)
{
	DIR		*ptr;
	char	*ret;

	if (is_dots(cmd))
		return (NULL);
	if (access(cmd, F_OK) != 0)
		no_file_dir(master, cmd);
	ptr = opendir(cmd);
	if (errno != 20)
	{
		if (ptr)
			if (closedir(ptr) == -1)
				clean_free(master, 1);
		print_error("minishell", cmd, "is a directory\n");
		clean_free(master, 126);
	}
	if (access(cmd, X_OK) == 0)
	{
		ret = ft_strdup(cmd);
		if (!ret)
			clean_free(master, 1);
		return (ret);
	}
	perm_denied(master, cmd);
	return (NULL);
}
