/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_separation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:48:07 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/25 03:47:32 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function that separates list of tokens into list of commands; Each command has a structure of t_command
 * Commands are separated by PIPE '|'
 * In case an invalid input is found no more tokens after that are stored
 * Commands are stored in the master structure as a linked list
*/
int	command_separation(t_master *master)
{
	t_token		*temp;
	t_command	*cmd;
	int			i;

	i = 1;
	temp = master->token_list;
	master->num_commands = count_commands(master);
	while (temp)
	{
		cmd = ft_calloc(1, sizeof(t_command));
		if (!cmd)
			clean_free(master, 1);
		cmd->cmd_nb = i;
		while (temp && temp->type != PIPE)
		{
			if (temp->type == ARG)
				add_to_command(temp, &cmd->args, master);
			else if (temp->type == OUTPUT || temp->type == APPEND)
				add_to_command(temp, &cmd->outputs, master);
			else if (temp->type == HEREDOC || temp->type == INPUT)
				add_to_command(temp, &cmd->inputs, master);
			if (temp->type == INPUT && !validate_file(temp->str))
			{
				cmd->inv_file = 1;
				temp = find_next_pipe(temp);
				break ;
			}
			temp = temp->next;
		}
		cmd->args_char = token_to_array(cmd->args, master);
		insert_in_list(cmd, master);
		if (temp && temp->type == PIPE)
			temp = temp->next;
		i++;
	}
	if (!master->token_list)
	{
		g_error = 0;
		return (0);
	}
	return (1);
}

/**
 * Finds first token of the following pipe
 * returns null if not existent
*/
t_token	*find_next_pipe(t_token *temp)
{
	while(temp && temp->type == PIPE)
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

/**
 * Adds the token to the end of **list
*/
void	add_to_command(t_token *member, t_token **list, t_master *master)
{
	t_token	*end;

	end = last_token(*list);
	if (end)
		end->next = copy_token(member, master);
	else
		*list = copy_token(member, master);
}

/**
 * Creates a deep copy of a given token
 * Returns the pointer to the created token
*/
t_token	*copy_token(t_token *src, t_master *master)
{
	t_token	*res;

	res = ft_calloc(1, sizeof(t_token));
	if (!res)
		clean_free(master, 1);
	res->str = ft_strdup(src->str);
	if (!res->str)
	{
		free(res);
		clean_free(master, 1);
	}
	res->type = src->type;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

/**
 * convierte token list en un doble array
*/
char    **token_to_array(t_token *token, t_master *master)
{
    char    **token_array;
    t_token *aux;
    int len;
    int i;

    aux = token;
    len = 0;
    while (aux != NULL)
    {
        len++;
        aux = aux->next;
    }
    token_array = (char **)ft_calloc((len + 1), sizeof(char *));
    if (!token_array)
		clean_free(master, 1);
    i = 0;
    while (i < len)
    {
        token_array[i] = ft_strdup(token->str);
		if(!token_array[i])
		{
			free_double_array(token_array);
			clean_free(master, 1);
		}
        token = token->next;
        i++;
    }
    return (token_array);
}
