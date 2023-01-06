/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:37:31 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/06 18:09:35 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	minishell_one(t_master *master)
{
	t_command	*cmd;
	
	cmd = master->commands_list;
	handle_outputs(cmd, master);
	if (close(master->fd[READ]) == -1)
		clean_free(master, 1);
	if (cmd->inv_file)
	{
		print_error("minishell", last_token(cmd->inputs)->str, "No such file or directory\n");
		g_error = 2;
		return ;
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
}

void	exec_bin_one(t_master *master, t_command *cmd)
{
	char	**path;
	char	*command;
	char	**env;
	int		pid;
	int		exit;

	pid = fork();
	if (pid == -1)
		clean_free(master, 1);
	if (pid == 0)
	{
		path = find_path(master);
		command = get_command(path, cmd->args_char[0], master);
		free_double_array(path);
		if(!command)
			exec_aux_free(cmd, master);
		path = copy_double_array(cmd->args_char);
		env = env_to_array(master->env);
		if (!path || !env)
			exec_aux_bin_free(command, path, env, master);
		clean_free_no_exit(master);
		execve(command, path, env);
		free_fail_exec(command, path, env);
	}
	if (waitpid(pid, &exit, 0) == -1)
		clean_free(master, 1);
	if (WIFEXITED(exit))
		g_error = WEXITSTATUS(exit);
}

void	reset_redirs(t_master *master)
{
	if(dup2(master->std_in, STDIN_FILENO) == -1)
		clean_free(master, 1);
	if(dup2(master->std_out, STDOUT_FILENO) == -1)
		clean_free(master, 1);
}

void	exec_aux_free(t_command *cmd, t_master *master)
{
	print_error("minishell", cmd->args_char[0], "command not found\n");
	clean_free(master, 127);
}