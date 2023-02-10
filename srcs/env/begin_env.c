/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:52:56 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 13:30:42 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "free.h"

static void	update_mshell(t_master *master, char *value)
{
	t_env	*env;

	env = master->env;
	while (env != NULL)
	{
		if (ft_strcmp(env->title, "MSHELL") == 0)
		{
			free (env->value);
			env->value = value;
			break ;
		}
		env = env->next;
	}
}

static void	check_mshell(t_master *master)
{
	char	*value;
	char	*title;

	if (find_in_env(master->env, "MSHELL"))
	{
		value = ft_strdup("0");
		if (!value)
			clean_free(master, 1);
		update_mshell(master, value);
	}
	else
	{
		title = ft_strdup("MSHELL");
		value = ft_strdup("1");
		if (!title || !value)
			free_aux_master(title, value, NULL, master);
		add_to_env(title, value, master);
	}
}

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
	check_mshell(master);
}
