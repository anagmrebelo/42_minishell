/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:17:47 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/31 21:59:01 by anarebelo        ###   ########.fr       */
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
