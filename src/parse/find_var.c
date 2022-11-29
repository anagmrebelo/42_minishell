/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:05:45 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/29 12:32:11 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Checks if it is alphanumeric or $
*/
_Bool	ok(char c)
{
	if (!ft_isalnum(c) && c != '$')
		return (0);
	return (1);
}

/**
 * Determines if $VAR is allowed to be substituted (if between simple quotes it shouldn't); 
 * If it is (allow_update == 1) and searches for variables named *str on the environment and returns its value; returns NULL if it does not find a match
 * returns $VAR if the substitution is not allowed
*/
char	*find_var(char *str, t_master *master, int pos, char *full_line)
{
	int		i;
	int		j;
	_Bool	allow_update;
	char	*ll;

	allow_update = 1;
	i = 0;
	j = -1;
	while (i < pos)
	{
		if (j < 0 && (full_line[i] == '\'' || full_line[i] == '\"' ))
		{
			j = i;
			if (full_line[i] == '\'')
				allow_update = 0;
		}
		else if (j >= 0 && full_line[i] == full_line[j])
		{
			j = -1;
			allow_update = 1;
		}	
		i++;
	}
	if (allow_update)
		return (find_aux(str, master));
	ll = ft_strjoin("$", str);
	free(str);
	return (ll);
}

char	*find_aux(char *str, t_master *master)
{
	t_env	*temp;
	
	if (ft_strncmp("$", str, find_max_len("$", str)) == 0)
	{
		free(str);
		return(ft_itoa(getpid()));	// Change for bash pid	GETPID is not allowed
	}
	temp = master->env;
	while (temp)
	{
		if (ft_strncmp(str, temp->title, find_max_len(str, temp->title)) == 0)
		{
			free(str);
			return (ft_strdup(temp->value));
		}
		temp = temp->next;
	}
	free(str);
	return (NULL);
}
