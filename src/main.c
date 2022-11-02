/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/15 14:22:02 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int main(int argc, char **argv, char **enviroment)
{
    t_master *master;

	if (argc >= 1 && argv)
	{
		master = malloc(sizeof(t_master));
	
	// ENVIRONMENT TESTING
		init_env(master, enviroment);
	//	print_env(master->env);
		
	// PARSING TESTING
		//char *line = argv[1];
		char *line = "\'\"\'";
		parsing(line, master);
		print_list_tokens(master->token_list);


	//FREE	
		free_list(master->token_list);
		free(master);
	}
	return (0);
}
