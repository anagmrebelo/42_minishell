/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:51:45 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:02:29 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	del_update(t_token *new)
{
	unsigned int	i;

	i = 0;
	if (ft_strlen(new->str) % 2 != 0)
		return ;
	while (new->str[i])
	{
		if (new->str[i] == new->str[i + 1]
			&& (new->str[i] == '\'' || new->str[i] == '\"'))
			i += 2;
		else
			return ;
	}
	new->no_del = 1;
}
