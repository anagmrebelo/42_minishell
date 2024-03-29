/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:38:03 by anarebelo         #+#    #+#             */
/*   Updated: 2023/02/09 23:07:04 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "free.h"
#include "utils.h"

void	print_error(char *minishell, char *builtin, char *message)
{
	ft_putstr_fd(minishell, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(builtin, 2);
	if (builtin)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
}

char	*create_message(t_master *master, char *message, char *token, char *msg)
{
	char	*temp;

	temp = ft_strjoin(message, token);
	if (!temp)
		clean_free(master, 1);
	temp = join_free_s1(temp, msg);
	if (!temp)
		clean_free(master, 1);
	return (temp);
}
