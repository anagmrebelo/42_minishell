/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:37:31 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/30 18:06:27 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	minishell_one(t_master *master)
{
	t_command	*cmd;

	cmd = master->commands_list;
	close(master->fd[READ]);
	handle_outputs(cmd, master);
	if (cmd->inv_file)
	{
		printf("minishell: %s: No such file or directory\n", last_token(cmd->inputs)->str);
		clean_free(master);
	}
	exec(master, cmd);
	return ;
}

void	exec_one(t_master *master, t_command *cmd)
{
	redir_inputs(cmd, master);
	redir_outputs(cmd, master);
	if (is_builtin(cmd->args_char[0]))
        exec_builtin(cmd->args_char[0], cmd, master->env); //@arebelo check leaks and reset dirs
	else
        exec_bin_one(master, cmd);
	reset_redirs_one(master);
}

void	exec_bin_one(t_master *master, t_command *cmd)
{
	char	**path;
	char	*command;
	char	**env;
	int		pid;

	pid = fork();
	if (pid == -1)
		clean_free(master);
	if (pid == 0)
	{
		path = find_path(master);
		command = get_command(path, cmd->args_char[0], master);
		if(!command)
			exec_aux_free(cmd, path, master);
		free(path);
		path = copy_double_array(cmd->args_char);
		env = env_to_array(master->env);
		clean_free_no_exit(master);
		execve(command, path, env);
		free_fail_exec(command, path, env);
	}
	waitpid(pid, NULL, 0);
}

void	reset_redirs_one(t_master *master)
{
	dup2(master->std_in, STDIN_FILENO);
	dup2(master->std_out, STDOUT_FILENO);
}

void	exec_aux_free(t_command *cmd, char **path, t_master *master)
{
	printf("minishell: %s: command not found\n", cmd->args_char[0]);
	free(path);
	clean_free(master);
}