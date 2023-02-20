/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:05:45 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 23:00:18 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "free.h"
#include "utils.h"
#include "expansions.h"

static char	*find_aux_here(char *str, t_master *master)
{
	t_env	*temp;
	char	*test;

	temp = master->env;
	if (ft_strcmp(str, "?") == 0)
	{
		free(str);
		test = ft_itoa(g_glbl.g_error);
		if (!test)
			clean_free(master, 1);
		return (test);
	}
	while (temp && str)
	{
		if (ft_strcmp(str, temp->title) == 0)
			return (create_str(str, temp, master));
		temp = temp->next;
	}
	if (str)
		free(str);
	return (NULL);
}

static char	*find_aux2_here(char *str, t_master *master)
{
	str = join_free_s2("$", str);
	if (!str)
		clean_free(master, 1);
	return (str);
}

/**
 * Determines if $VAR is allowed to be substituted 
 (if between simple quotes it shouldn't); 
 * If it is (allow_update == 1) and searches for variables named *str on 
 the environment and returns its value; returns NULL if it does not find a match
 * returns $VAR if the substitution is not allowed
*/
char	*find_here(char *str, t_master *master, int pos, char *full_line)
{
	int		i;
	int		j;
	_Bool	allow_update;

	allow_update = 1;
	i = 0;
	j = -1;
	while (i < pos)
	{
		if (j < 0 && (full_line[i] == '\'' || full_line[i] == '\"' ))
			j = i;
		else if (j >= 0 && full_line[i] == full_line[j])
		{
			j = -1;
			allow_update = 1;
		}	
		i++;
	}
	if (allow_update)
		return (find_aux_here(str, master));
	return (find_aux2_here(str, master));
}
