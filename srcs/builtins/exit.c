/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:33:20 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/09 13:08:08 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit_error(int n, char *str)
{
	if (n == 1)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	if (n == 2)
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("numeric argument required", 2);
	}
}

static int	is_numeric(char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	if (len == 1)
	{
		if (ft_isdigit(str[0]))
			return (0);
		else
			return (1);
	}
	i = 1;
	while (str[i])
	{
		if (str[0] == '-' || str[0] == '+' || ft_isdigit(str[0]))
		{
			if (ft_isdigit(str[i]))
				i++;
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

static int	checknum(char *str)
{
	if (ft_strcmp(str, "9223372036854775807") > 0)
		return (1);
	else if (str[0] == '-' && ft_strcmp(str, "-9223372036854775807") > 0)
		return (1);
	return (0);
}

static int	aux_exit(char **args, t_master *master)
{
	int	n;

	n = 0;
	if (is_numeric(args[1]) || checknum(args[1]))
	{
		print_exit_error(2, args[1]);
		master->status = 1;
		n = 255;
	}
	else if (!is_numeric(args[1]) && !args[2])
	{
		n = ft_atoi(args[1]);
		ft_putendl_fd("exit", 2);
		master->status = 1;
		if (n < 0)
		n *= -255;
	}
	return (n % 256);
}

int	ft_exit(char **args, t_master *master)
{
	int	n;

	if (master->num_commands > 1)
	{
		n = ft_atoi(args[1]);
		return (n);
	}
	if (!args[1])
	{
		ft_putendl_fd("exit", 2);
		master->status = 1;
		return (g_error);
	}
	else if (args[2] && !is_numeric(args[1]))
	{
		print_exit_error(1, NULL);
		return (1);
	}
	else if (args[1])
		return (aux_exit(args, master));
	return (0);
}
