/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:24:30 by arebelo           #+#    #+#             */
/*   Updated: 2022/10/18 19:29:04 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 * Transforms char * line from readline into tokens
*/
void	parsing(char *line, t_master *master)
{
	int	i;

	i = 0;
	while (line[i])
		i += tokenize(&line[i], master);
	return ;
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
	while (line[i] && (line[i] != ' ' || quotes > 0))
	{
		if (quotes < 0 && (line[i] == '\'' || line[i] == '\"'))
			quotes = i;
		else if (quotes > 0 && line[i] == line[quotes])
			quotes = -1;
		i++;
	}
	if (i != 0)
	{
		new = new_token(line, i, master);
		if (new)
			add_list(master, new);
	}
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

/**
 * Creates an instance of token (all initialized as zero)
 * Adds the string component of the token
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
	env_update(new, master);
	quotes_update(new);
	return (new);
}
