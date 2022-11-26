/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:58:11 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/26 16:58:14 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_init_redirs(t_master *master)
{
	close(master->std_in);
	close(master->std_out);
}