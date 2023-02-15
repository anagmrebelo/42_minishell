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
#include <termios.h>

// static	void	handle_signal(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		g_global.g_error = 1;
// 	}
// 	else if (signal == SIGQUIT)
// 	{
// 		rl_on_new_line();
// 		rl_redisplay();
// 		g_global.g_error = 1;
// 	}
// }

// static void	handle_sig_exec(int signal)
// {
// 	if (signal == SIGQUIT)
// 	{
// 		write(1, "Quit: 3\n", 8);
// 		g_global.g_error = 131;
// 	}
// 	else if (signal == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		g_global.g_error = 130;
// 	}
// }

// static void	handle_child(int signal)
// {
// 	if (signal == SIGQUIT)
// 		g_global.g_error = 131;
// 	else if (signal == SIGINT)
// 		g_global.g_error = 130;
// }

// static void	handle_sig_here(int signal)
// {
// 	if (signal == SIGQUIT)
// 		g_global.g_error = 131;
// 	else if (signal == SIGINT)
// 	{
// 		close(STDIN_FILENO);
// 		write(STDOUT_FILENO, "> \n", 3);
// 		g_global.g_ctrlc = 1;
// 		g_global.g_error = 130;
// 	}
// }

static void	handle_signals(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_signals_heredoc(int sig)
{
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "> \n", 3);
		g_glbl.g_ctrlc = 1;
		g_glbl.g_error = 1;
	}
}

void	init_signal(int mode, t_env *env)
{
	struct sigaction	sa;
	// struct termios	term;
	// if (tcgetattr(STDIN_FILENO, &term) == -1)
	// 	return ;
	// term.c_lflag &= ~ECHOCTL;
	// if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	// 	return ;
	(void)env;
	sa.sa_flags = SA_SIGINFO;
	if (mode == 1)
		sa.sa_handler = SIG_IGN;
	else if (mode == 2)
		sa.sa_handler = &handle_signals_heredoc;
	else if (mode == 3)
		sa.sa_handler = &handle_signals;
	else if (mode == 0)
		sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
