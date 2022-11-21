#include "../../include/minishell.h"

void pipe_separation(t_master *master)
{
	t_token	*temp;
	t_pipe	*pipe;

	temp = master->token_list;
	master->numPipe = count_pipes(master);

	while (temp)
	{
		pipe = ft_calloc(1, sizeof(t_pipe));
	 	if (!pipe)
	 		break; // Fix to exit program
	 	while (temp && temp->type != PIPE)
	 	{
	 		if(temp->type == ARG)
	 			add_to_pipe(temp, pipe->args);
			else if (temp->type == OUTPUT || temp->type == APPEND)
				add_to_pipe(temp, pipe->outputs);
			else if (temp->type == HEREDOC || temp->type == INPUT)
				add_to_pipe(temp, pipe->inputs);
			if(temp->type == INPUT && !validate_file(temp->str))
			{
				pipe->inv_file = 1;
				break;
			}
	 		temp = temp->next;
	 	}
	 	insert_in_list(pipe, master);
	 	if(temp && temp->type == PIPE)
	 		temp = temp->next;
	}
	print_pipes(master);
	return ;
}

int	count_pipes(t_master *master)
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

_Bool	validate_file(char *path)
{
	(void) path;
	return (1);
}

void	insert_in_list(t_pipe *member, t_master *master)
{
	t_pipe	*temp;

	if (master->pipes_list)
	{
		temp = master->pipes_list;
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
		master->pipes_list = member;
}

void	add_to_pipe(t_token *member, t_token *list)
{
	t_token	*end;

	end = last_token(list);
	if (end)
	{
		end->next = member;
		end->next->next = NULL;
	}	
	else
	{
		list = member;
		list->next = NULL;
	}
}