/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2022/11/25 22:12:15 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **enviroment)
{
	t_master	*master;
	char		*line;

	if (argc >= 1 && argv)
	{
		master = ft_calloc(1, sizeof(t_master));
		if (!master)
			return (1);
		init_env(master, enviroment);
		while (!master->status)
		{
			line = readline(YELLOW"minishell: "RESET);
			master->status = add_hist_exit_check(line);
			if (master->status)
				break ;
			minishell(line, master);
		}
		clean_free(master);
	}
}

_Bool	add_hist_exit_check(char *line)
{
	add_history(line);
	if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	minishell(char *line, t_master *master)
{
	t_command	*cmd;

	init_redirs(master);
	if (parsing(line, master))
	{
		cmd = master->commands_list;
		while (cmd)
		{
			if (cmd->cmd_nb != 1)
				dup2(master->fd[READ], STDIN_FILENO);
			close(master->fd[READ]);
			pipe(master->fd);
			master->pid = fork();
			if (master->pid < 0)
				break;	//Correct
			if (master->pid == 0)
				if (handle_redirs(cmd, master))
					exec(master, cmd);
			close(master->fd[WRITE]);
			waitpid(master->pid, NULL, 0);
			cmd = cmd->next;
		}
		close(master->fd[READ]);
		dup2(master->std_in, STDIN_FILENO);
		prep_next_line(master);
		close_init_redirs(master);
	}
}

void	clean_free(t_master *master)
{
	free_env_lst(master->env);
	free (master);
	return ;
}
