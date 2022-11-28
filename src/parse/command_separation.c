#include "../../include/minishell.h"

/**
 * Function that separates list of tokens into list of commands; Each command has a structure of t_command
 * Commands are separated by PIPE '|'
 * In case an invalid input is found no more tokens after that are stored
 * Commands are stored in the master structure as a linked list
*/
void command_separation(t_master *master)
{
	t_token		*temp;
	t_command	*cmd;
	int			i;

	i = 1;
	temp = master->token_list;
	master->numCommands = count_commands(master);
	while (temp)
	{
		cmd = ft_calloc(1, sizeof(t_command));
	 	if (!cmd)
	 		break; // Fix to exit program
		cmd->cmd_nb = i;
	 	while (temp && temp->type != PIPE)
	 	{
	 		if(temp->type == ARG)
				add_to_command(temp, &cmd->args);
			else if (temp->type == OUTPUT || temp->type == APPEND)
				add_to_command(temp, &cmd->outputs);
			else if (temp->type == HEREDOC || temp->type == INPUT)
				add_to_command(temp, &cmd->inputs);
			if(temp->type == INPUT && !validate_file(temp->str))
			{
				cmd->inv_file = 1;
				temp = NULL;
				break;
			}
	 		temp = temp->next;
	 	}
		cmd->args_char = token_to_array(cmd->args);
	 	insert_in_list(cmd, master);
	 	if(temp && temp->type == PIPE)
	 		temp = temp->next;
		i++;
	}
	return ;
}

/**
 * Returns the number of commands to be executed
 * Stored in t_master
*/
int	count_commands(t_master *master)
{
	int	i;
	t_token *temp;

	i = 1;
	temp = master->token_list;
	while(temp)
	{
		if(temp->type == PIPE)
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
		while(temp)
		{
			if(!temp->next)
			{
				temp->next = member;
				break;
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
void	add_to_command(t_token *member, t_token **list)
{
	t_token	*end;

	end = last_token(*list);
	if (end)
		end->next = copy_token(member);
	else
		*list = copy_token(member);	
}

/**
 * Creates a deep copy of a given token
 * Returns the pointer to the created token
*/
t_token	*copy_token(t_token *src)
{
	t_token	*res;

	res = ft_calloc(1, sizeof(t_token));
	if (!res)
		return (res);
	res->str = ft_strdup(src->str);
	if (!res->str)
		printf("Error on function copy_token\n");	// change to exit program
	res->type = src->type;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

/**
 * Frees the list of commands stored in t_master
*/
void	free_commands(t_master *master)
{
	t_command	*list;
	t_command	*temp;

	list = master->commands_list;
	while(list)
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
}

