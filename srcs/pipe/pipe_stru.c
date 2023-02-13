/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stru.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:04:55 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 16:04:42 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "free.h"
#include "exec.h"

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
	if (i == 1)
		return ;
	while (i--)
	{
		j = 0;
		pid = waitpid(-1, &j, 0);
		if (pid == -1)
			clean_free(master, 1);
		if (pid == master->pid)
		{
			if (WIFEXITED(j))
				g_global.g_error = WEXITSTATUS(j);
		}
	}
}

/**
 * Initiates signals
 * Parses
 * And opens pipes if necessary
*/
void	minishell(t_master *master)
{
	init_signal(0, master->env);
	if (parsing(master))
	{
		if (master->num_commands == 1)
			minishell_one(master);
		else
			minishell_multi(master);
	}
	wait_childs(master);
	prep_next_line(master);
}
