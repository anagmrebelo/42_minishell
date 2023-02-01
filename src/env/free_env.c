/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:39:22 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/01 16:40:30 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
