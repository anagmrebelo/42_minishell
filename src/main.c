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
	
	//EXEC
	char **path;
	char *command;
	char **str;

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
        	if (ft_strncmp(line, "exit", find_max_len(line, "exit	")) == 0)	//Forbidden function
			{
				i = 0;
				free(line);
			}
    		else
        	{
            	if (line[0] == '\0')
               		i = 1;
            	else
				{
					//PARSING
					parsing(line, master);
					print_list_tokens(master->token_list);
					
					//EXECVE
					str = token_to_array(master->token_list);
					path = find_path(master);
					command = get_command(path, master->token_list->str);
					if (execve(command, str, enviroment) == -1)
						printf("error execve\n");
					
					free_list(master);
				}
       		}
   		}	
		
		//FREE
		free_env_lst(master->env);
		free (master);
	}
}
