/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:17:45 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/17 10:32:38 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

//free del contenido de la lista y la lista
void	free_lst(t_list *env)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free (tmp2->title);
		free (tmp2->value);
		free(tmp2);
	}
	free (env);
	env = NULL;
	tmp = NULL;
	tmp2 = NULL;
}
