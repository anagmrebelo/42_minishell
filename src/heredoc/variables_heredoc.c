/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:34:33 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/28 22:31:59 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*aux1_here(char *read, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(read, c[J], c[I] - c[J]);
	if (!temp)
		clean_free(master, 1);
	line = join_double_free(line, temp);
	if (!line)
	{
		free(temp);
		clean_free(master, 1);
	}	
	c[J] = ++c[I];
	return (line);
}

char	*aux2_here(char *read, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(read, c[J], 1);
	if (!temp)
		clean_free(master, 1);
	line = join_double_free(line, find_here(temp, master, c[J], read));
	if (!line)
	{
		free(temp);
		clean_free(master, 1);
	}
	c[J] = c[I] + 1;
	return (line);
}

char	*aux3_here(char *read, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(read, c[J], c[I] - c[J]);
	if (!temp)
		clean_free(master, 1);
	line = join_double_free(line, find_here(temp, master, c[J], read));
	if (!line)
	{
		free(temp);
		clean_free(master, 1);
	}
	c[J] = c[I]--;
	return (line);
}

char	*aux4_here(char *read, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(read, c[J], c[I] - c[J]);
	if (!temp)
		clean_free(master, 1);
	line = join_double_free(line, temp);
	if (!line)
	{
		free(temp);
		clean_free(master, 1);
	}
	return (line);
}


/**
 * Analyses the str from token and substitutes $ for the environment variables, if there is a match
 * It only substitutes if after the $ there is an alphanumeric and it is not between simple quotes
 * If there is $$ it should print minishell pid
*/
char	*heredoc_update(char *read, t_master *master)
{
	int		c[2];
	char	*line;

	if (ft_strrchr(read, '$') == NULL)
		return (read);
	c[I] = -1;
	c[J] = 0;
	line = NULL;
	while (read[++c[I]])
	{
		if (read[c[I]] == '$' && read[c[I] + 1] && ok(read[c[I] + 1]))
		{
			line = aux1_here(read, master, line, c);
			if (ft_isdigit(read[c[I]]))
				c[I]++;
			else
				while (read[c[I]] && ok(read[c[I]]) && read[c[I]] != '$' && read[c[I]] != '?')
					c[I]++;
			if (c[J] == c[I])
				line = aux2_here(read, master, line, c);
			else
				line = aux3_here(read, master, line, c);
		}
	}
	if (c[J] != c[I])
		line = aux4_here(read, master, line, c);
	free(read);
	return (line);
}