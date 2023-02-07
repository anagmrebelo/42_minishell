/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:07:42 by anarebelo         #+#    #+#             */
/*   Updated: 2023/02/07 18:59:15 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_command_aux(char *path_cmd, char **path, t_master *master)
{
	print_error("minishell", path_cmd, "Permission denied\n");
	free(path_cmd);
	free_path_master(NULL, path, master, 126);
}

//Prueba en cada direccion de path si encuentra el comando necesario
//y lo devuelve en formato "/bin/ls"
char	*get_command(char **path, char *cmd, t_master *master)
{
	int		i;
	char	*aux;
	char	*path_cmd;

	i = 0;
	if (is_dots(cmd) || !path || check_path(path, cmd, master) || is_path(cmd))
		return (executable(cmd, master));
	while (path[i])
	{
		aux = ft_strjoin(path[i++], "/");
		if (!aux)
			free_path_master(aux, path, master, 1);
		path_cmd = join_free_s1(aux, cmd);
		if (!path_cmd)
			free_path_master(aux, path, master, 1);
		if (access(path_cmd, F_OK) == 0)
		{
			if (access(path_cmd, X_OK) == 0)
				return (path_cmd);
			get_command_aux(path_cmd, path, master);
		}
		free(path_cmd);
	}
	if (path_bin(path))
		return (executable(cmd, master));
	return (NULL);
}

void	free_path_master(char *aux, char **path,
	t_master *master, int exit_code)
{
	if (aux)
		free(aux);
	if (path)
		free_double_array(path);
	clean_free(master, exit_code);
}
