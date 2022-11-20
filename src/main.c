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
	//char **array;

	if (argc >= 1 && argv)
	{
		master = ft_calloc(1, sizeof(t_master));	//we have to protect master

		//ENV
		init_env(master, enviroment);
		//print_env(master->env);
		//array = env_to_array(master->env);
		//free_array(array);
		//print_sort_env(master->env);
		
		i = 1;
		while (i)
   		{
        	line = readline("minishell: ");
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
					if(parsing(line, master))
						print_list_tokens(master->token_list);
					free_list(master);
				}
       		}
   		}	
		
		//FREE
		free_env_lst(master->env);
		free (master);
	}
}
