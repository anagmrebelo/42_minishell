/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/17 17:03:16 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int main(int argc, char **argv, char **enviroment)
{
    t_master *master;

	if (argc >= 1 && argv)
	{
		master = malloc(sizeof(t_master));
		master->env = NULL;
		master->env_array = NULL;
		init_env(master, enviroment);
		//print_env(master->env);
		printf("len list: [%d]\n", len_lst(master->env));
		lst_to_array(master);
		env_to_export(master->env);
		free_lst(master->env);
		free (master);
	}
}
