/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:13:21 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/10 17:03:00 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(char *str, int fd)
{
	ft_putstr_fd(str, fd);
}

static int	check_n(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 2;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		if (arg[2])
		{
			while (arg[i])
			{
				if (arg[i] == 'n' || arg[i] == '\0')
					i++;
				else
					return (0);
			}
		}
		return (1);
	}
	return (0);
}

static int	do_echo(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		print_echo(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	return (i);
}

int	ft_echo(char **args)
{
	int	i;
	int	flag;

	args = &args[1];
	flag = 0;
	if (!args[0])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	if (check_n(args[0]))
	{
		if (ft_strcmp(args[0], "-n") == 0 && !args[1])
			return (0);
		i = 0;
		while (check_n(args[i]))
			i++;
		flag = 1;
		args = &args[i];
	}
	i = do_echo(args);
	if (!args[i] && !flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
