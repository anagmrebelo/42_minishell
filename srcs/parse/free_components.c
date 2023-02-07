/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:43:31 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/31 17:45:46 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Frees line and sets it to null
*/
void	free_line(t_master *master)
{
	if (master->line)
		free(master->line);
	master->line = NULL;
}

/**
 * Frees exec variables in case of execve failure
*/
void	free_fail_exec(char *command, char **path, char **env)
{
	if (command)
		free(command);
	free_double_array(path);
	free_double_array(env);
	exit(0);
}

/**
 * Frees the list of commands stored in t_master
*/
void	free_commands(t_master *master)
{
	t_command	*list;
	t_command	*temp;

	list = master->commands_list;
	while (list)
	{
		temp = list->next;
		free_command(list);
		free(list);
		list = temp;
	}
	master->commands_list = NULL;
}

/**
 * Frees each command
*/
void	free_command(t_command *command)
{
	free_token_list(command->args);
	free_token_list(command->inputs);
	free_token_list(command->outputs);
	free_double_array(command->args_char);
	command->args = NULL;
	command->inputs = NULL;
	command->outputs = NULL;
	command->args_char = NULL;
}
