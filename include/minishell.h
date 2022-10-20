/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/19 16:37:19 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <../libft/libft.h>

typedef struct s_env
{
	char *content;
	char *title;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct s_master
{
    t_env *env;
}   t_master;

//ENVIROMENT
int		init_env(t_master *master, char **enviroment);
t_env	*new_env(char *content, char *title, char *value);
char    *get_title(char *str);
char    *get_value(char *str);
void	add_back(t_env *env, t_env *new);
t_env	*last_env(t_env *env);
void	print_env(t_env *env);
void    free_env(t_env *item);
void    free_env_lst(t_env *list);
char    **env_to_array(t_env *env);
int 	env_len(t_env *env);
void    free_array(char **array);


//UTILS
char	*join_free(char *s1, char *s2);

#endif
