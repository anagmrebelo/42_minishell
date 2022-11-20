/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:37:57 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/20 18:39:27 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_list_tokens(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d: %s  -> type: %d\n", i, list->str, list->type);
		list = list->next;
		i++;
	}
}
