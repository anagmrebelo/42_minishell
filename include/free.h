/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:50:53 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:54:13 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

void	clean_free(t_master *master, int exit_code);
void	clean_free_no_exit(t_master *master);
void	prep_next_line(t_master *master);
void	free_master(t_master *master);

#endif
