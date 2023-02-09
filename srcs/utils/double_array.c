/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:11:03 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 14:51:06 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * Frees a double pointer
*/
void	free_double_array(char **table)
{
	int		i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
}

/**
 * Creates a deep copy of a given char**
*/
char	**copy_double_array(char **src)
{
	size_t	i;
	char	**cpy;

	i = 0;
	cpy = NULL;
	while (src && src[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		cpy[i] = ft_strdup(src[i]);
		if (!cpy[i])
		{
			free_double_array(cpy);
			return (NULL);
		}
		i++;
	}
	return (cpy);
}
