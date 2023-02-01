/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:03:23 by anarebelo         #+#    #+#             */
/*   Updated: 2023/02/01 11:44:33 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin(char *command, t_command *cmd, t_env *env, t_master *master)
{
	if (strcmp(command, "echo") == 0)
		return (ft_echo(cmd->args_char));
	else if (ft_strcmp(command, "cd") == 0)
		return (ft_cd(env, cmd->args_char));
	else if (ft_strcmp(command, "pwd") == 0)
		return (ft_pwd(env));
	else if (ft_strcmp(command, "export") == 0)
		return (ft_export(env, cmd->args_char, master));
	else if (ft_strcmp(command, "unset") == 0)
		return (ft_unset(env, cmd->args_char));
	else if (ft_strcmp(command, "env") == 0)
		return (ft_env(env));
	else if (ft_strcmp(command, "exit") == 0)
		return (ft_exit(cmd->args_char, master));
	return (0);
}

int	is_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}
