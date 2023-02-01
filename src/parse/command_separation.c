/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_separation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:48:07 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/01 19:01:38 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function that separates list of tokens into list of commands;
 * Each command has a structure of t_command
 * Commands are separated by PIPE '|'
 * In case an invalid input is found no more tokens after that are stored
 * Commands are stored in the master structure as a linked list
*/
int	command_separation(t_master *master)
{
	t_token		*temp;
	t_command	*cmd;
	int			cmd_nb;

	cmd = NULL;
	cmd_nb = 1;
	temp = master->token_list;
	master->num_commands = count_commands(master);
	while (temp)
	{
		cmd = ft_calloc(1, sizeof(t_command));
		if (!cmd)
			clean_free(master, 1);
		temp = adding_sort(temp, cmd, master, cmd_nb);
		cmd_nb++;
	}
	if (!master->token_list)
	{
		g_error = 0;
		return (0);
	}
	return (1);
}

t_token	*adding_sort(t_token *temp, t_command *cmd,
	t_master *master, int cmd_nb)
{
	cmd->cmd_nb = cmd_nb;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == ARG)
			add_to_command(temp, &cmd->args, master);
		else if (temp->type == OUTPUT || temp->type == APPEND)
			add_to_command(temp, &cmd->outputs, master);
		else if (temp->type == HEREDOC || temp->type == INPUT)
			add_to_command(temp, &cmd->inputs, master);
		if ((temp->type == INPUT && !validate_input(temp, cmd))
			|| ((temp->type == OUTPUT || temp->type == APPEND)
				&& !validate_output(temp->str, cmd, master)))
		{
			temp = find_next_pipe(temp);
			break ;
		}
		temp = temp->next;
	}
	cmd->args_char = token_to_array(cmd->args, master);
	insert_in_list(cmd, master);
	if (temp && temp->type == PIPE)
		temp = temp->next;
	return (temp);
}

/**
 * Finds first token of the following pipe
 * returns null if not existent
*/
t_token	*find_next_pipe(t_token *temp)
{
	while (temp && temp->type == PIPE)
		temp = temp->next;
	if (!temp || !temp->next)
		return (NULL);
	else
		return (temp->next);
}

/**
 * Returns the number of commands to be executed
 * Stored in t_master
*/
int	count_commands(t_master *master)
{
	int		i;
	t_token	*temp;

	i = 1;
	temp = master->token_list;
	while (temp)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

/**
 * Inserts commands at the end of the list stored in t_master
*/
void	insert_in_list(t_command *member, t_master *master)
{
	t_command	*temp;

	if (master->commands_list)
	{
		temp = master->commands_list;
		while (temp)
		{
			if (!temp->next)
			{
				temp->next = member;
				break ;
			}	
			temp = temp->next;
		}
	}
	else
		master->commands_list = member;
}
