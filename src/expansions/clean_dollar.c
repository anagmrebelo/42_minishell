/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:24:58 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/04 00:27:59 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Returns the str without the char at position i
*/
char	*clean_dollar(char *str, int i, t_master *master, char *fre)
{
	char	*ret;

	ret = ft_calloc(ft_strlen(str) + 1, 1);
	if (!ret)
	{
		free(fre);
		free(str);
		clean_free(master, 1);
	}
	ft_strlcpy(ret, str, ft_strlen(str) + 1);
	ft_strlcpy(ret + i, ret + i + 1, ft_strlen(str) + 1);
	ret[ft_strlen(str)] = 0;
	free(str);
	return (ret);
}

/**
 * Looks for "" or '' directly after $
 * In the case of existing deletes $ from str
*/
char	*remove_dollar(char *str, t_master *master)
{
	char	*ret;
	int		i;

	i = 0;
	ret = str;
	while (ret[i] && ret[i + 1])
	{
		if (ret[i] == '$' && (ret[i + 1] == '\'' || ret[i + 1] == '\"'))
			ret = clean_dollar(ret, i, master, str);
		i++;
	}
	return (ret);
}