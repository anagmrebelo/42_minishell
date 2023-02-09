/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:07:40 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 23:09:52 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "free.h"

static char	*free_aux_join(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (NULL);
}

/**
 * Function equivalent to ft_strnjoin however it frees both 
 * strings passed as arguments
*/
char	*join_double_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	new = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!new)
		return (free_aux_join(s1, s2, NULL));
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		new[i + j] = s2[j];
	free(s1);
	if (s2)
		free(s2);
	return (new);
}

/**
 * Function equivalent to ft_strnjoin however it frees s1
 */
char	*join_free_s1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	new = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!new || !s1)
		return (free_aux_join(new, s1, NULL));
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	if (!s2)
	{
		free(s1);
		return (new);
	}
	while (s2[++j])
		new[i + j] = s2[j];
	free(s1);
	return (new);
}

/**
 * Function equivalent to ft_strnjoin however it frees s2
 */
char	*join_free_s2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;
	int		mal;

	mal = 0;
	if (!s1 && mal++ == 0)
		s1 = ft_calloc(1, sizeof(char));
	new = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if ((!new && (s1 && !mal)) || !s1)
		return (free_aux_join(s2, NULL, NULL));
	else if (!new && (s1 && mal))
		return (free_aux_join(s2, s1, NULL));
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		new[i + j] = s2[j];
	if (mal)
		free(s1);
	if (s2)
		free(s2);
	return (new);
}


char	*free_aux_master(char *s1, char *s2, char *s3, t_master *master)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	clean_free(master, 1);
	return (NULL);
}
