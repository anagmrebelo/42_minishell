/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:39:22 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/09 16:02:59 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "free.h"

void	free_env(t_env *item)
{
	if (item)
	{
		free(item->title);
		if (item->value)
			free(item->value);
		free(item);
	}
}

void	free_env_lst(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list->next;
		free_env(list);
		list = tmp;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free (array[i]);
		i++;
	}
	free(array);
}

void	free_array_master(char **array, t_master *master)
{
	free_double_array(array);
	clean_free(master, 1);
}
