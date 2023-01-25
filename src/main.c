/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2023/01/25 04:11:31 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_launch_minishell(char *line, char **enviroment)
{
	t_master	*master;

	master = ft_calloc(1, sizeof(t_master));
	if (!master)
		return (1);
	init_env(master, enviroment);
	init_redirs(master);
	master->line = ft_strdup(line);
	if (!master->line)
		clean_free(master, 1);
	add_hist_exit_check(master);
	if (master->line == 0)
	{
		free_master(master);
		exit (1);
	}
	if (*master->line != '\0')
	{
		add_history(master->line);
		minishell(master->line, master);
	}
	close_init_redirs(master);
	free_master(master);
	exit(g_error);
}

int	main(int argc, char **argv, char **enviroment)
{
	t_master	*master;

	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
  	{
    	int exit_status = ft_launch_minishell(argv[2], enviroment);
    	exit(exit_status);
 	}
	if (argc >= 1 && argv)
	{
		master = ft_calloc(1, sizeof(t_master));
		if (!master)
			return (1);
		init_env(master, enviroment);
		init_redirs(master);
		while (!master->status)
		{
			master->line = readline(YELLOW"minishell: "RESET);
			master->status = add_hist_exit_check(master);
			if (master->status)
				break ;
			if (master->line == 0)
			{
				free_master(master);
				exit (1);
			}
			if (*master->line != '\0')
			{
				add_history(master->line);
				minishell(master->line, master);
			}
			else
				free_line(master);
		}
		close_init_redirs(master);
		free_master(master);
	}
	return (g_error);
}

/**
 * If line is empty and original STDIN is not a terminal (e.g. is a file) changes master->status to 1 to end minishell loop and finish parent process
*/
_Bool	add_hist_exit_check(t_master *master)
{
	if (isatty(STDIN_FILENO) == 0 && !master->line)
		return (1);
	return (0);
}

/**
 * Waits for all child processes
 * if there is only one command, the waitpid is done in the function exec_bin_one
*/
void	wait_childs(t_master *master)
{
	int	i;
	int	pid;
	int	j;

	i = master->num_commands;
	if(i == 1)
		return ;
	while(i--)
	{
		j = 0;
		pid = waitpid(-1, &j, 0);
		if (pid == -1)
			clean_free(master, 1);
		if (pid == master->pid)
		{
			if (WIFEXITED(j))
				g_error = WEXITSTATUS(j);
		}
	}
}

void	child1(t_master *master, t_command *cmd)
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

void	parent2(t_master *master)
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

void	minishell(char *line, t_master *master)
{
	t_command	*cmd;

	if (parsing(line, master))
	{
		if (master->num_commands == 1)
			minishell_one(master);
		else
		{
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
					child1(master, cmd);
					exec(master, cmd);
				}
				parent2(master);
				cmd = cmd->next;
			}
		}
	}
	wait_childs(master);
	prep_next_line(master);
}