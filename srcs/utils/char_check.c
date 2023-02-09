/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:17:47 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 01:04:57 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Returns true if space, tab, pipe or redirs
*/
_Bool	is_delimeter(char c)
{
	if (is_space(c) || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

_Bool	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

/**
 * Checks if cmd is . or ..
*/
_Bool	is_dots(char *cmd)
{
	if (ft_strlen(cmd) == 1 && *cmd == '.')
		return (1);
	else if (ft_strlen(cmd) == 2 && cmd[0] == '.' && cmd[1] == '.')
		return (1);
	return (0);
}

/**
 * Changes '\'' for non printable char 27 and '\"' for non-printable char 28
*/
char	*do_non_print(char *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (a[i] == '\'')
			a[i] = 27;
		if (a[i] == '\"')
			a[i] = 28;
		i++;
	}
	return (a);
}

/**
 * Changes non printable char 27 for '\'' and non-printable char 28 for '\"'
*/
char	*undo_non_print(char *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (a[i] == 27)
			a[i] = '\'';
		if (a[i] == 28)
			a[i] = '\"';
		i++;
	}
	return (a);
}
