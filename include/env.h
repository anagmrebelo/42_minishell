/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:14:00 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/10 17:39:37 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

void	begin_env(char **environment, t_master *master);
int		init_env(t_master *master, char **enviroment);
t_env	*new_env(char *title, char *value, t_master *master);
char	*get_title(char *str, t_master *master);
char	*get_value(char *str, t_master *master);
void	add_back(t_env *env, t_env *new);
void	print_env(t_env *env);
void	free_env(t_env *item);
void	free_env_lst(t_env *list);
char	**env_to_array(t_master *master);
int		env_len(t_env *env);
void	free_array(char **array);
void	free_array_master(char **array, t_master *master);
void	print_sort_env(t_master *master);
char	*getvar_value(t_master *master, char *title);
char	*getvar_value_env(char **env, char *title);
int		default_env(t_master *master);
int		find_in_env(t_env *env, char *str);
void	update_shlvl(t_master *master);
void	var_update(t_master *master);
void	create_shlvl(t_master *master);

#endif
