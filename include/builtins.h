/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:45:46 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/10 17:49:31 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		ft_echo(char **args);
int		ft_pwd(t_env *env);
int		ft_cd(t_env *env, char **args, t_master *master);
char	*get_env_value(char *title, t_env *env);
void	update_env(char *oldpwd, t_env *env, t_master *master);
int		update_pwd(t_env *env, t_master *master);
void	update_oldpwd(char *oldpwd, t_env *env, t_master *master);
int		change_dir(char *arg, char *oldpwd, t_env *env, t_master *master);
int		ft_env(t_env *env);
int		ft_unset(t_env *env, char **args);
int		ft_export(t_env *env, char **args, t_master *master);
void	add_to_env(char *title, char *value, t_master *master);
void	print_export_error(char *str);
int		first_check(char *str);
int		var_title_check(char *str);
int		ft_exit(char **args, t_master *master);

#endif
