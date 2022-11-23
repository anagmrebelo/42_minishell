/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/19 16:41:39 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int main(int argc, char **argv, char **enviroment)
{
    t_master	*master;
	char		*line;
	int			i;
	t_command	*cmd;
	
	//EXEC
	// char **path;
	// char *command;
	// char **str;

	if (argc >= 1 && argv)
	{
		master = ft_calloc(1, sizeof(t_master));  //we have to protect master

		//ENV
		init_env(master, enviroment);
		i = 1;
		while (i)
   		{
        	line = readline("minishell: ");
			add_history(line);
        	if (ft_strncmp(line, "exit", find_max_len(line, "exit")) == 0)	//Forbidden function
			{
				i = 0;
				free(line);
			}
    		else
        	{
            	// if (line[0] == '\0')		//Ask Mica if it is necessary
               	// 	i = 1;
            	// else
				// {
					//PARSING
					init_redirs(master);
					if (parsing(line, master))
					{
						cmd = master->commands_list;
						while (cmd)
						{
							if (handle_redirs(cmd, master))
								exec(master, cmd);
							adjust_redirs(cmd, master);
							cmd = cmd->next;
						}
					// }
					prep_next_line(master);
				}
       		}
   		}	
		
		//FREE
		close_init_redirs(master);
		free_env_lst(master->env);
		free (master);
	}
}
