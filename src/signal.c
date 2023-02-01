/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:24:46 by mrollo            #+#    #+#             */
/*   Updated: 2023/01/31 23:56:14 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_signal(int signal)
{
    if (signal == SIGINT)
    {
        //rl_replace_line("", 0);
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

// void    handle_sigint(int signal)
// {
//     (void)signal;
//     rl_replace_line("", 0);
//     write(1, "\n", 1);
//     rl_on_new_line();
//     rl_redisplay();
//     g_error = 1;
// }

// void    handle_sigquit(int signal)
// {
//     (void)signal;
//     rl_on_new_line();
//     rl_redisplay();
//     g_error = 1;
// }

void    handle_sig_exec(int signal)
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

void    init_signal(int i)
{
    struct sigaction    sa;

    sa.sa_flags = SA_RESTART;
    if (i)
    {
        sa.sa_handler = &handle_signal;
        //signal(SIGINT, handle_sigint);
        //signal(SIGQUIT, handle_sigquit);
    }
    else
    {
        sa.sa_handler = &handle_sig_exec;
        //signal(SIGQUIT, handle_sig_exec);
        //signal(SIGINT, handle_sig_exec);
    }
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}