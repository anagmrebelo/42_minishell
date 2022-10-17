/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/17 12:30:16 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <../libft/libft.h>

typedef struct s_master
{
    t_list *env;
	char	**env_array;
}   t_master;

int		init_env(t_master *master, char **enviroment);
char    *get_title(char *str);
char    *get_value(char *str);
void	print_env(t_list *env);
void	free_lst(t_list *env); //nueva
int		len_lst(t_list *env);
//char	**lst_to_array(t_list *env);
void	lst_to_array(t_master *master);
int		env_mem(t_list *env, t_master *master);

#endif
