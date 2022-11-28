/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2022/11/28 15:59:49 by arebelo          ###   ########.fr       */
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
	if (line && ft_strcmp(line, "exit") == 0)
	{
		if(line)
			free(line);
		return (1);
	}
	if (isatty(STDIN_FILENO) == 0 && !line)
		return(1);
	return (0);
}

void	minishell(char *line, t_master *master)
{
	t_command	*cmd;

	init_redirs(master);
	if (parsing(line, master))
	{
		if(master->numCommands == 1)
			minishell_one(master);
		else
		{
			cmd = master->commands_list;
			while (cmd)
			{
				handle_pipe(master, cmd);
				master->pid = fork();
				if (master->pid < 0)
					break ; //Correct + close fd[write]
				if (master->pid == 0)
					if(handle_redirs(cmd, master))
						exec(master, cmd);
				close(master->fd[WRITE]);
				waitpid(master->pid, NULL, 0);
				cmd = cmd->next;
			}
		}
		prep_next_line(master);
	}
}

void	clean_free(t_master *master)
{
	free_env_lst(master->env);
	free (master);
	return ;
}

void	minishell_one(t_master *master)
{
	t_command *cmd;

	cmd = master->commands_list;
	close(master->fd[READ]);
	handle_outputs(cmd);
	if(cmd->inv_file)
	{
		close(master->fd[WRITE]);
		printf("minishell: %s: No such file or directory\n", last_token(cmd->inputs)->str);
		return ;
	}
	exec(master, cmd);
	return ;
}

void exec_one(t_master *master, t_command *cmd)
{
    char    **path;
    char    *command;
    char    **env;
	int	 	pid;

	pid = fork();
	//protect
	if (pid == 0)
	{
		redir_inputs(cmd);
		redir_outputs(cmd, master);
		path = find_path(master);
		command = get_command(path, cmd->args_char[0]);
		env = env_to_array(master->env);
		execve(command, cmd->args_char, env);	
		exit(1);// Adjust
	}
	waitpid(pid, NULL, 0);
}