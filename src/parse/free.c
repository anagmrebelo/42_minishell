/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:55:49 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/29 10:56:21 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
    
void    free_master(t_master *master)
{
	free_line(master);
	free_env_lst(master->env);  //Suggestion: change arg to only master to avoid next line
	master->env = NULL;
	free_token_list(master->token_list);
	master->token_list = NULL;
	free_commands(master);
	if(master)
		free(master);
}

void	free_line(t_master *master)
{
	if(master->line)
		free(master->line);
	master->line = NULL;
}

void	clean_free_pipe_read(t_master *master)
{
	close(master->fd[WRITE]);
	close_init_redirs(master);
	free_master(master);
	exit(1);
}