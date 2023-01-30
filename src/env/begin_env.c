/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:52:56 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/30 19:56:21 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Creates an environment with the default variables, in the case of minishell being initiated with no env
 *	Transforms the char** into t_env* list stored in master 
*/
void	begin_env(char **environment, t_master *master)
{
	if (!*environment)
		default_env(master);
	else
		init_env(master, environment);
}