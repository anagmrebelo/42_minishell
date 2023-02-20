/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stru.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:04:55 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/20 11:53:01 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "free.h"
#include "exec.h"

static void	aux_wait_childs(int code)
{
	if (code == 130)
		ft_putendl_fd("^C", STDOUT_FILENO);
	if (code == 131)
		ft_putstr_fd("^\\", STDOUT_FILENO);
}

/**
 * Waits for all child processes
 * if there is only one command, the waitpid is done in the function exec_bin_one
*/
static void	wait_childs(t_master *master)
{
	int	i;
	int	pid;
	int	j;

	i = master->num_commands;
	init_signal(1);
	if (i == 1)
		return ;
	while (i--)
	{
		j = 0;
		pid = waitpid(-1, &j, 0);
		if (pid == -1)
			clean_free(master, 1);
		if (i == 0 && WIFSIGNALED(j))
		{
			j += 128;
			aux_wait_childs(j);
		}
		else if (pid == master->pid)
			if (WIFEXITED(j))
				g_glbl.g_error = WEXITSTATUS(j);
	}
}

/**
 * Initiates signals
 * Parses
 * And opens pipes if necessary
*/
void	minishell(t_master *master)
{
	if (parsing(master))
	{
		init_signal(0);
		if (master->num_commands == 1)
			minishell_one(master);
		else
		{
			minishell_multi(master);
			wait_childs(master);
		}
	}
	prep_next_line(master);
}
