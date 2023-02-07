/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:36:26 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/01 12:49:31 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Expands '~' to home directory if is surrounded by spaces or it has a '/' after
 * or represents a valid path
*/
void	home_update(t_token *new, t_master *master)
{
	unsigned int	i;

	i = 0;
	if (ft_strrchr(new->str, '~') == NULL)
		return ;
	while (new->str[i])
	{
		if (new->str[i] == '~')
		{
			if (i == 0 || (i > 0 && is_space(new->str[i - 1])))
			{
				if (i == (ft_strlen(new->str) - 1)
					|| (is_space(new->str[i + 1]) || new->str[i + 1] == '/'))
					home_join(new, master, i);
				if (is_valid_path(&new->str[i + 1], master))
					users_join(new, master, i);
			}
		}
		i++;
	}
}

/**
 * Checks if after ~ exists a valid path substituting ~ by /Users/
*/
_Bool	is_valid_path(char *str, t_master *master)
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
	return (0);
}

/**
 * Returns string with one more expansion of '~' from variable HOME or getenv
*/
void	home_join(t_token *new, t_master *master, unsigned int i)
{
	char	*home;
	char	*before;
	char	*after;

	home = getvar_value(master, "HOME");
	if (!home)
		home = getenv("HOME");
	if (!home)
		return ;
	before = ft_substr(new->str, 0, i);
	after = ft_substr(new->str, i + 1, ft_strlen(new->str) - i);
	if (!before || !after)
		clean_free(master, 1);
	free(new->str);
	new->str = join_free_s1(before, home);
	if (!new->str)
		clean_free(master, 1);
	new->str = join_double_free(new->str, after);
	if (!new->str)
		clean_free(master, 1);
}

/**
 * Returns string with one more expansion of '~' of /Users/
*/
void	users_join(t_token *new, t_master *master, unsigned int i)
{
	char	*home;
	char	*before;
	char	*after;

	home = "/Users/";
	before = ft_substr(new->str, 0, i);
	after = ft_substr(new->str, i + 1, ft_strlen(new->str) - i);
	if (!before || !after)
		clean_free(master, 1);
	free(new->str);
	new->str = join_free_s1(before, home);
	if (!new->str)
		clean_free(master, 1);
	new->str = join_double_free(new->str, after);
	if (!new->str)
		clean_free(master, 1);
}
