/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:52:56 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/10 17:21:25 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "utils.h"
#include "free.h"
#include "builtins.h"

/**
 * Creates an environment with the default variables, 
 in the case of minishell being initiated with no env
 *	Transforms the char** into t_env* list stored in master 
*/
void	begin_env(char **environment, t_master *master)
{
	if (!*environment)
		default_env(master);
	else
		init_env(master, environment);
}
