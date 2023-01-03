/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:38:03 by anarebelo         #+#    #+#             */
/*   Updated: 2023/01/03 16:44:55 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	print_error(char *bash, char *builtin, char *message, int error_code)
{
	ft_putstr_fd(bash, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(builtin, 2);
	if (builtin)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	g_error = error_code;
}

char	*create_message(t_master *master, char *message, char *token, char *msg)
{
	char	*temp;

	temp = ft_strjoin(message, token);
	if (!temp)
		clean_free_pipe_read(master, 1);
	temp = join_free_s1(temp, msg);
	if (!temp)
		clean_free_pipe_read(master, 1);
	return (temp);
}