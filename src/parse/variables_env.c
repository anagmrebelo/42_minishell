/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:34:33 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/25 03:48:39 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Analyses the str from token and substitutes $ for the environment variables, if there is a match
 * It only substitutes if after the $ there is an alphanumeric and it is not between simple quotes
 * If there is $$ it should print minishell pid
*/
void	env_update(t_token *new, t_master *master)
{
	int		c[2];
	char	*line;

	if (ft_strrchr(new->str, '$') == NULL)
		return ;
	c[I] = -1;
	c[J] = 0;
	line = NULL;
	while (new->str[++c[I]])
	{
		if (new->str[c[I]] == '$' && new->str[c[I] + 1] && ok(new->str[c[I] + 1]))
		{
			line = aux1_env(new, master, line, c);
			if (ft_isdigit(new->str[c[I]]))
				c[I]++;
			else
				while (new->str[c[I]] && ok(new->str[c[I]]) && new->str[c[I]] != '$' && new->str[c[I]] != '?')
					c[I]++;
			if (c[J] == c[I])
				line = aux2_env(new, master, line, c);
			else
				line = aux3_env(new, master, line, c);
		}
	}
	if (c[J] != c[I])
		line = aux4_env(new, master, line, c);
	free(new->str);
	new->str = line;
}

char	*aux1_env(t_token *new, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(new->str, c[J], c[I] - c[J]);
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

char	*aux2_env(t_token *new, t_master *master, char *line, int *c)
{
	char	*temp;
	temp = ft_substr(new->str, c[J], 1);
	if (!temp)
		clean_free(master, 1);
	line = join_double_free(line, find_var(temp, master, c[J], new->str));
	if (!line)
	{
		free(temp);
		clean_free(master, 1);
	}
	c[J] = c[I] + 1;
	return (line);
}

char	*aux3_env(t_token *new, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(new->str, c[J], c[I] - c[J]);
	if (!temp)
		clean_free(master, 1);
	line = join_double_free(line, find_var(temp, master, c[J], new->str));
	if (!line)
	{
		free(temp);
		clean_free(master, 1);
	}
	c[J] = c[I]--;
	return (line);
}

char	*aux4_env(t_token *new, t_master *master, char *line, int *c)
{
	char	*temp;

	temp = ft_substr(new->str, c[J], c[I] - c[J]);
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
