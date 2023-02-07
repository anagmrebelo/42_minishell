/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:18:50 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/07 01:09:49 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	minishell_multi(t_master *master)
{
	t_command	*cmd;

	cmd = master->commands_list;
	while (cmd)
	{
		if (pipe(master->fd) == -1)
			clean_free(master, 1);
		master->pid = fork();
		if (master->pid < 0)
		{
			close(master->fd[WRITE]);
			close(master->fd[READ]);
			clean_free(master, 1);
		}
		if (master->pid == 0)
		{
			child(master, cmd);
			exec(master, cmd);
		}
		parent(master);
		cmd = cmd->next;
	}
}

void	child(t_master *master, t_command *cmd)
{
	_Bool	i;

	i = 0;
	if (cmd->cmd_nb != master->num_commands)
		if (dup2(master->fd[WRITE], STDOUT_FILENO) == -1)
			i = 1;
	if (close(master->fd[WRITE]) == -1)
		i = 1;
	if (close(master->fd[READ]) == -1)
		i = 1;
	if (i)
		clean_free(master, 1);
	handle_outputs(cmd, master);
	handle_redirs(cmd, master);
}

void	parent(t_master *master)
{
	_Bool	i;

	i = 0;
	if (dup2(master->fd[READ], STDIN_FILENO) == -1)
		i = 1;
	if (close(master->fd[0]) == -1)
		i = 1;
	if (close(master->fd[1]) == -1)
		i = 1;
	if (i)
		clean_free(master, 1);
}
