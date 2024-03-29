/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:55:49 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/22 11:43:59 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "redir.h"
#include "env.h"
#include <unistd.h>

void	clean_free_no_exit(t_master *master)
{
	close_init_redirs(master);
	free_master(master);
}

void	clean_free(t_master *master, int exit_code)
{
	clean_free_no_exit(master);
	exit(exit_code);
}

void	prep_next_line(t_master *master)
{
	if (unlink(".hdoc") && errno != 2)
		clean_free(master, 1);
	reset_redirs(master);
	free_token_list(master->token_list);
	master->token_list = NULL;
	free_commands(master);
	free_line(master);
}

void	free_master(t_master *master)
{
	free_line(master);
	free_env_lst(master->env);
	master->env = NULL;
	free_token_list(master->token_list);
	master->token_list = NULL;
	free_commands(master);
	if (master)
		free(master);
}
