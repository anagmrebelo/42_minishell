/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/15 14:20:31 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <../libft/libft.h>

/*
typedef struct s_list
{
    char    *title;
    char    *value;
    char    *content;
    struct s_list   *next;
}   t_list;
*/
typedef struct s_master
{
    t_list *env;
}   t_master;

int		init_env(t_master *master, char **enviroment);
char    *get_title(char *str);
char    *get_value(char *str);
void	print_env(t_list *env);

#endif
