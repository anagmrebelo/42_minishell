/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:09:00 by anarebelo         #+#    #+#             */
/*   Updated: 2023/02/01 11:52:27 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec(t_master *master, t_command *cmd)
{
	if (master->num_commands == 1)
		exec_one(master, cmd);
	else if (!cmd->args_char[0])
		exit(0);
	else if (is_builtin(cmd->args_char[0]))
		exit(exec_builtin(cmd->args_char[0], cmd, master->env, master));
	else
		exec_bin(master, cmd);
	return (0);
}

//ejecuta los comandos en un child process
void	exec_bin(t_master *master, t_command *cmd)
{
	char	**path;
	char	*command;
	char	**env;

	path = find_path(master);
	command = get_command(path, cmd->args_char[0], master);
	free_double_array(path);
	if (!command)
		exec_aux_free(cmd, master);
	path = copy_double_array(cmd->args_char);
	env = env_to_array(master->env);
	if (!path || !env)
		exec_aux_bin_free(command, path, env, master);
	clean_free_no_exit(master);
	execve(command, path, env);
	free_fail_exec(command, path, env);
}

void	exec_aux_bin_free(char *command, char**path,
	char **env, t_master *master)
{
	if (command)
		free(command);
	if (path)
		free_double_array(path);
	if (env)
		free_double_array(env);
	clean_free(master, 1);
}

void	exec_aux_free(t_command *cmd, t_master *master)
{
	if (ft_strlen(cmd->args_char[0]) == 1 && *(cmd->args_char[0]) == '.')
	{
		print_error("minishell", cmd->args_char[0],
			"filename argument required\n");
		clean_free(master, 2);
	}
	print_error("minishell", cmd->args_char[0], "command not found\n");
	clean_free(master, 127);
}
