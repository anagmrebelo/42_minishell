/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:17:47 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/30 22:48:46 by arebelo          ###   ########.fr       */
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
