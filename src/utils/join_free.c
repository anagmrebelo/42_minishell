/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:07:40 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/31 18:08:39 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * (1 + 1));
		s1[0] = '\0';
	}
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (0);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	free(s1);
	return (new);
}

/**
 * Equivalent to ft_strlen but protects against NULL argument
*/
size_t	ft_strlen_null(const char *str)
{
	int	n;

	n = 0;
	if (!str)
		return (n);
	while (str[n])
		n++;
	return (n);
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
	new = (char *)ft_calloc((ft_strlen_null(s1) + ft_strlen_null(s2) + 1),
			sizeof(char));
	if (!new)
		return (0);
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
	new = (char *)ft_calloc((ft_strlen_null(s1) + ft_strlen_null(s2) + 1),
			sizeof(char));
	if (!new)
		return (0);
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

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	new = (char *)ft_calloc((ft_strlen_null(s1) + ft_strlen_null(s2) + 1),
			sizeof(char));
	if (!new)
		return (0);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	if (!s2)
		return (new);
	while (s2[++j])
		new[i + j] = s2[j];
	free(s2);
	return (new);
}

char	*free_aux_join(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (NULL);
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
