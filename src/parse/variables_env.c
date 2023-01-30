/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:34:33 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/30 22:41:03 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Analyses the str from token and substitutes $ for the environment variables, if there is a match
 * It only substitutes if after the $ there is an alphanumeric and it is not between simple quotes
 * If there is $$ it should print minishell pid
*/
char	*env_update(char *read, t_master *master, char *line)
{
	int		c[2];

	if (ft_strrchr(read, '$') == NULL)
		return (master->line);
	c[I] = -1;
	c[J] = 0;
	while (read[++c[I]])
	{
		if (read[c[I]] == '$' && read[c[I] + 1] && ok(read[c[I] + 1]))
		{
			line = aux1_env(read, master, line, c);
			if (ft_isdigit(read[c[I]]))
				c[I]++;
			else
				while (aux5_env(read, c))
					c[I]++;
			if (c[J] == c[I])
				line = aux2_env(read, master, line, c);
			else
				line = aux3_env(read, master, line, c);
		}
	}
	if (c[J] != c[I])
		line = aux4_env(read, master, line, c);
	return (line);
}

char	*aux1_env(char *read, t_master *master, char *line, int *c)
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

char	*aux2_env(char *read, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(read, c[J], 1);
	if (!temp)
		clean_free(master, 1);
	line = join_double_free(line, find_var(temp, master, c[J], read));
	if (!line)
	{
		free(temp);
		clean_free(master, 1);
	}
	c[J] = c[I] + 1;
	return (line);
}

char	*aux3_env(char *read, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(read, c[J], c[I] - c[J]);
	if (!temp)
		clean_free(master, 1);
	line = join_double_free(line, find_var(temp, master, c[J], read));
	if (!line)
	{
		free(temp);
		clean_free(master, 1);
	}
	c[J] = c[I]--;
	return (line);
}

char	*aux4_env(char *read, t_master *master, char *line, int *c)
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
