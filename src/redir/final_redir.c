/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:58:11 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/06 17:17:38 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Closes file descriptors initially saved with dup 
*/
void	close_init_redirs(t_master *master)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (master->std_in != -1)
		i = close(master->std_in);
	if (master->std_out != -1)
		j = close(master->std_out);
	if (i == -1 || j == -1)
	{
		free_master(master);
		exit(1);
	}
}