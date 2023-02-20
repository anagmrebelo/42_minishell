/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:24:46 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/20 10:59:10 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "free.h"
#include <termios.h>

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

void	set_term(t_master *master)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		clean_free(master, 1);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		clean_free(master, 1);
}

void	init_signal(int mode)
{
	struct sigaction	sa;

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
