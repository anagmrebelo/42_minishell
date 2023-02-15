/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:37:31 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 22:51:02 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "errors.h"
#include "redir.h"
#include "free.h"

void	minishell_one(t_master *master)
{
	t_command	*cmd;

	cmd = master->commands_list;
	handle_outputs(cmd, master);
	if (cmd->inv_file || cmd->inv_perm || cmd->not_dir)
	{
		if (cmd->inv_file)
			print_error("minishell", last_token(cmd->failed)->str,
				"No such file or directory\n");
		else if (cmd->inv_perm)
			print_error("minishell", (last_token(cmd->failed))->str,
				"Permission denied\n");
		else
			print_error("minishell", (last_token(cmd->failed))->str,
				"Not a directory\n");
		g_global.g_error = 1;
		return ;
	}
	redir_outputs(cmd, master);
	redir_inputs(cmd, master);
	exec(master, cmd);
	return ;
}

static void	exec_bin_one(t_master *master, t_command *cmd)
{
	int		pid;
	int		code;

	pid = fork();
	if (pid == -1)
		clean_free(master, 1);
	if (pid == 0)
		exec_bin(master, cmd);
	init_signal(1, master->env);
	if (waitpid(pid, &code, 0) == -1)
		clean_free(master, 1);
	if (WIFSIGNALED(code))
	{
		code += 128;
		if (code == 130)
			ft_putchar_fd('\n', STDOUT_FILENO);
		if (code == 131)
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		g_global.g_error = code;
	}
	else if (WIFEXITED(code))
		g_global.g_error = WEXITSTATUS(code);
}

void	exec_one(t_master *master, t_command *cmd)
{
	redir_inputs(cmd, master);
	redir_outputs(cmd, master);
	if (!cmd->args_char[0] || !*cmd->args_char[0])
	{
		g_global.g_error = 0;
		return ;
	}
	if (is_builtin(cmd->args_char[0]))
		g_global.g_error = exec_builtin(cmd->args_char[0], cmd, master->env, master);
	else
		exec_bin_one(master, cmd);
}
