/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:17:04 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/17 12:30:47 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int len_lst(t_list *env)
{
    int len;
    t_list  *tmp;

    len = 0;
    tmp = env;
    while (tmp != NULL)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}

int	env_mem(t_list *env, t_master *master)
{
	int	len;

	len = len_lst(env);
    master->env_array = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!master->env_array)
		return (1);
	return (len);
}
