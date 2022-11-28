/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:24:30 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/26 17:38:24 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 * Transforms char * line from readline into tokens
*/
_Bool	parsing(char *line, t_master *master)
{
	int	i;

	i = 0;
	if(!check_quotes(line))
	{
		printf("Error: Quotes not closed\n");	//change to perror
		if(line)
			free(line);
		return (0);
	}
	while (line[i])
		i += tokenize(&line[i], master);
	if (check_syntax(master))
	{
		add_types_redir(master);
		clean_tokens(master);
		if(line)
		{
			free(line);
			line = NULL;
		}
		command_separation(master);
		return (1);
	}
	printf("Syntax Error\n");	// Handle error
	return (0);
}

_Bool	isDelimeter(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')	// add tabs
		return (1);
	return (0); 
}

/**
 * Function that creates token and sets i to last char or last space before starting new word
*/
int	tokenize(char *line, t_master *master)
{
	int		i;
	int		quotes;
	t_token	*new;

	i = 0;
	quotes = -1;
	while (line[i] && (!isDelimeter(line[i]) || quotes >= 0 ))
	{
		if (quotes < 0 && (line[i] == '\'' || line[i] == '\"'))
			quotes = i;
		else if (quotes >= 0 && line[i] == line[quotes])
			quotes = -1;
		i++;
	}
	if (i == 0)
	{
		if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
			i++;
		else if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
			i++;
		i++;
	}
	new = new_token(line, i, master);
	if (new)
		add_list(master, new);
	while (line[i] && line[i] == ' ')	//add tabs
		i++;
	return (i);
}

/**
 * Creates an instance of token (all initialized as zero)
 * Adds the string component of the token
 * Adds type to the token if it is '>' or '>>' or '<' or '<<' or '|'
 * Calls function to convert env variables $ into its value (env_update)
 * Calls function to clean the sring of closed quotes (quotes_update)
*/
t_token	*new_token(char *line, int size, t_master *master)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_substr(line, 0, size);
	if (new->str == NULL)
	{
		//Deal with error
	}
	add_type(new);
	env_update(new, master);
	quotes_update(new);
	return (new);
}

/**
 * Deletes tokens that have an empty str
*/
void	clean_tokens(t_master *master)
{
	t_token	*temp;

	temp = master->token_list;
	while(temp)
	{
		if (!temp->str || !temp->str[0])
			delete_token(temp, master);
		temp = temp->next;
	}
}