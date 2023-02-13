/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:24:46 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/09 13:31:16 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static	void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_error = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_error = 1;
	}
}

static void	handle_sig_exec(int signal)
{
	if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_error = 131;
	}
	else if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_error = 130;
	}
}

static void	handle_child(int signal)
{
	if (signal == SIGQUIT)
		g_error = 131;
	else if (signal == SIGINT)
		g_error = 130;
}

static void	handle_sig_here(int signal)
{
	if (signal == SIGQUIT)
		g_error = 131;
	else if (signal == SIGINT)
	{
		g_ctrlc = 1;
		g_error = 130;
	}
}

void	init_signal(int i, t_env *env)
{
	struct sigaction	sa;
	int					mshell;

	sa.sa_flags = SA_RESTART;
	if (i)
		sa.sa_handler = &handle_signal;
	if (i == 3)
		sa.sa_handler = &handle_sig_here;
	else if (i == 0)
	{
		mshell = ft_atoi(get_env_value("MSHELL", env));
		if (mshell)
			sa.sa_handler = &handle_sig_exec;
		else
			sa.sa_handler = &handle_child;
	}
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
