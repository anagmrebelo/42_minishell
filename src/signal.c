/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:24:46 by mrollo            #+#    #+#             */
/*   Updated: 2022/12/29 18:24:48 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_sigint(int signal)
{
    (void)signal;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

void    handle_sigquit(int signal)
{
    (void)signal;
    rl_on_new_line();
    rl_redisplay();
}

void    handle_sig_exec(int signal)
{
    if (signal == SIGQUIT)
    {
        write(1, "Quit: 3\n", 8);
    }
    else if (signal == SIGINT)
        return ;
}

void    init_signal(int i)
{
    if (i)
    {
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);
    }
    else
    {
        signal(SIGQUIT, handle_sig_exec);
        signal(SIGINT, handle_sig_exec);
    }
}