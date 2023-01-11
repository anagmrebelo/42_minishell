#include "../../include/minishell.h"

/**
 * When creating the token assign type;
 * files will be assigned as ARG and in function add_types_redir will be updated to the correct type
*/
void	add_type(t_token *new)
{
	if (new && new->str)
	{
		if (!ft_strcmp(new->str, ">"))
			new->type = OUTPUT;
		else if (!ft_strcmp(new->str, ">>"))
			new->type = APPEND;
		else if (!ft_strcmp(new->str, "<"))
			new->type = INPUT;
		else if (!ft_strcmp(new->str, "<<"))
			new->type = HEREDOC;
		else if (!ft_strcmp(new->str, "|"))
			new->type = PIPE;
		else
			new->type = ARG;
	}
}

/**
 * First condition: < >
 * Second condition: | |
 * Third condition | < >
*/
_Bool	check_exceptions(t_token *fst, t_token *scnd)
{
	if (fst->type < 5 && scnd->type)
		return (1);
	if (fst->type == 5 && scnd->type == 5)
		return (1);	
	return (0);
}

/**
 * verifies that special symbols are not consecutive (with some exceptions)
*/
_Bool	check_syntax(t_master *master)
{
	t_token	*temp;
	char	*message;
	
	temp = master->token_list;
	while(temp)
	{
		if(temp->type > 0)
		{
			if (!temp->next || check_exceptions(temp, temp->next))
			{
				if (!temp->next)
				{
					message = ft_strdup("syntax error near unexpected token \'newline\'\n");
					if(!message)
						clean_free_pipe_read(master, 1);
				}
				else
					message = create_message(master, "syntax error near unexpected token \'", temp->next->str, "\'\n");
				print_error("minishell", NULL, message);
				g_error = 258;
				free(message);
				return (0);
			}
		}
		temp = temp->next;
	}
	return (1);
}


/**
 * Update the tokens giving the ones after redirection the propper type
 * Tokens with the character (e.g. '>') will be empied and in function clean tokens will be later deleted
*/
void	add_types_redir(t_master *master)
{
	t_token	*temp;

	temp = master->token_list;
	while(temp)
	{
		if(temp->type > 0 && temp->type < 5)
		{
				temp->next->type = temp->type;
				free(temp->str);
				temp->str = NULL;
				temp = temp->next;
		}
		temp = temp->next;
	}
}