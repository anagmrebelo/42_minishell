/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:36:26 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/10 17:41:07 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "free.h"
#include "env.h"
#include "utils.h"

/**
 * Checks if after ~ exists a valid path substituting ~ by /Users/
*/
static _Bool	is_valid_path(char *str, t_master *master)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && !is_space(str[i]) && str[i] != '/')
		i++;
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		clean_free(master, 1);
	tmp = join_free_s2("/Users/", tmp);
	if (!tmp)
		clean_free(master, 1);
	if (!access(tmp, F_OK))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

/**
 * Returns string with one more expansion of '~' from variable HOME or getenv
*/
static void	home_join(t_master *master, unsigned int i)
{
	char	*home;
	char	*before;
	char	*after;

	home = getvar_value(master, "HOME");
	if (!home)
		home = getenv("HOME");
	if (!home)
		return ;
	before = ft_substr(master->line, 0, i);
	after = ft_substr(master->line, i + 1, ft_strlen(master->line) - i);
	if (!before || !after)
		clean_free(master, 1);
	free(master->line);
	master->line = join_free_s1(before, home);
	if (!master->line)
		clean_free(master, 1);
	master->line = join_double_free(master->line, after);
	if (!master->line)
		clean_free(master, 1);
}

/**
 * Returns string with one more expansion of '~' of /Users/
*/
static void	users_join(t_master *master, unsigned int i)
{
	char	*home;
	char	*before;
	char	*after;

	home = "/Users/";
	before = ft_substr(master->line, 0, i);
	after = ft_substr(master->line, i + 1, ft_strlen(master->line) - i);
	if (!before || !after)
		clean_free(master, 1);
	free(master->line);
	master->line = join_free_s1(before, home);
	if (!master->line)
		clean_free(master, 1);
	master->line = join_double_free(master->line, after);
	if (!master->line)
		clean_free(master, 1);
}

/**
 * Expands '~' to home directory if is surrounded by spaces or it has a '/' after
 * or represents a valid path
*/
void	home_update(t_master *master)
{
	unsigned int	i;

	i = 0;
	if (ft_strrchr(master->line, '~') == NULL)
		return ;
	while (master->line[i])
	{
		if (master->line[i] == '~')
		{
			if (i == 0 || (i > 0 && is_space(master->line[i - 1])))
			{
				if (i == (ft_strlen(master->line) - 1)
					|| (is_space(master->line[i + 1])
						|| master->line[i + 1] == '/'))
					home_join(master, i);
				if (is_valid_path(&master->line[i + 1], master))
					users_join(master, i);
			}
		}
		i++;
	}
}
