/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:58:11 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/29 10:27:00 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Closes file descriptors initially saved with dup 
*/
void	close_init_redirs(t_master *master)
{
	if (master->std_in != -1)
		close(master->std_in);
	if (master->std_out != -1)
		close(master->std_out);
}