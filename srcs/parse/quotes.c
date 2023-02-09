/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:41:32 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 01:41:47 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 * Function that checks if all quotes are closed
 * Returns 0 if not closed;
*/
_Bool	check_quotes(char *line)
{
	int		i;
	int		j;
	_Bool	allow_update;	

	allow_update = 1;
	i = 0;
	j = -1;
	while (line[i])
	{
		if (j < 0 && (line[i] == '\'' || line[i] == '\"' ))
		{
			j = i;
			allow_update = 0;
		}
		else if (j >= 0 && line[i] == line[j])
		{
			j = -1;
			allow_update = 1;
		}	
		i++;
	}
	return (allow_update);
}

/**
 * Function that creates a new char* cleaned of quotes 
*/
char	*quotes_clean(t_token *new, t_master *master)
{
	int		i;
	int		j;
	char	*clean;

	i = 0;
	clean = ft_calloc((ft_strlen(new->str) + 1), sizeof(char));
	if (!clean)
		clean_free(master, 1);
	while (new->str[i])
	{
		j = i;
		while (new->str[i] && new->str[i] != '\'' && new->str[i] != '\"')
			i++;
		ft_strlcat(clean, &new->str[j], ft_strlen(clean) + i - j + 1);
		if (!new->str[i])
			return (clean);
		j = i++;
		while (new->str[i] && new->str[i] != new->str[j])
			i++;
		ft_strlcat(clean, &new->str[j + 1], ft_strlen(clean) + i++ - j);
	}
	return (clean);
}

/**
 * Function that frees initial str of token with quotes and also eliminates
 * excessive memory in char* from quotes_clean
*/
void	quotes_update(t_token *ne, t_master *master)
{
	char	*temp;

	quotes_heredoc(ne);
	temp = ne->str;
	ne->str = quotes_clean(ne, master);
	free(temp);
	temp = ne->str;
	ne->str = ft_strdup(ne->str);
	free(temp);
	if (!ne->str)
		clean_free(master, 1);
	ne->str = undo_non_print(ne->str);
}

/**
 * Checks if there are quotes in the token->str
 * If it finds, changes token->here to true
*/
void	quotes_heredoc(t_token *ne)
{
	int	i;

	i = 0;
	while (ne->str[i])
	{
		if (ne->str[i] == '\'' || ne->str[i] == '\"')
		{
			ne->here = 1;
			return ;
		}
		i++;
	}
}
