/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/20 10:57:46 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"
#include "pipe.h"
#include "free.h"
#include "env.h"

int	ft_launch_minishell(char *line, char **environment)
{
	t_master	*master;

	master = ft_calloc(1, sizeof(t_master));
	if (!master)
		return (1);
	begin_env(environment, master);
	init_redirs(master);
	master->line = ft_strdup(line);
	if (!master->line)
		clean_free(master, 1);
	if (master->line == 0)
	{
		free_master(master);
		exit (1);
	}
	if (*master->line != '\0')
	{
		add_history(master->line);
		minishell(master);
	}
	close_init_redirs(master);
	free_master(master);
	exit(g_glbl.g_error);
}

/**
 * If line is empty and original STDIN is not a terminal (e.g. is a file) 
 * changes master->status to 1 to end minishell loop and finish parent process
*/
static _Bool	isatty_check(t_master *master)
{
	if (isatty(STDIN_FILENO) == 0 && !master->line)
		return (1);
	return (0);
}

static void	readline_loop(t_master *master)
{
	init_signal(3, master->env);
	set_term();
	master->line = readline(YELLOW"minishell: "RESET);
	master->status = isatty_check(master);
	if (master->status)
		return ;
	if (master->line == 0)
	{
		printf("exit\n");
		free_master(master);
		exit (0);
	}
	if (*master->line != '\0')
	{
		add_history(master->line);
		minishell(master);
	}
	else
		free_line(master);
	init_signal(1, master->env);
}

int	main(int argc, char **argv, char **environment)
{
	t_master	*master;

	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
  	{
		int exit_status = ft_launch_minishell(argv[2], environment);
		exit(exit_status);
 	}
	if (argc >= 1 && argv)
	{
		master = ft_calloc(1, sizeof(t_master));
		if (!master)
			return (1);
		g_glbl.g_ctrlc = 0;
		g_glbl.g_error = 0;
		begin_env(environment, master);
		init_redirs(master);
		while (!master->status)
			readline_loop(master);
		close_init_redirs(master);
		free_master(master);
	}
	return (g_glbl.g_error);
}
