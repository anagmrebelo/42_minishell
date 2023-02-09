/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:26:34 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:49:27 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "minishell.h"
int		exec_builtin(char *command, t_command *cmd,
			t_env *env, t_master *master);
int		is_builtin(char *command);
void	minishell_multi(t_master *master);
void	minishell_one(t_master *master);
void	exec_one(t_master *master, t_command *cmd);
char	**find_path(t_master *master);
_Bool	is_path(char *cmd);
_Bool	path_bin(char **path);
_Bool	check_path(char **path, char *cmd, t_master *master);
char	*executable(char *cmd, t_master *master);
int		exec(t_master *master, t_command *cmd);
void	exec_bin(t_master *master, t_command *cmd);
char	*get_command(char **path, char *cmd, t_master *master);

#endif
