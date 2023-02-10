/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:15:36 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/09 13:34:21 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	aux_numarray(char const *s, char c);
static unsigned long	aux_len(const char *s, char c);
static void				aux_fill_malloc(char **ptr, const char *s, char c);
static int				aux_space(unsigned long num_arr, char **ptr,
							char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char			**ptr;
	unsigned long	num_arr;
	const char		*temp;

	if (!s)
		return (0);
	temp = s;
	num_arr = aux_numarray(s, c);
	ptr = malloc((num_arr + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	if (!aux_space(num_arr, ptr, s, c))
	{
		free(ptr);
		return (0);
	}
	ptr[num_arr] = 0;
	aux_fill_malloc(ptr, temp, c);
	return (ptr);
}

static int	aux_space(unsigned long num_arr, char **ptr, char const *s, char c)
{
	unsigned long	num;

	num = 0;
	while (num < num_arr)
	{
		ptr[num] = malloc(aux_len(s, c) + 1);
		if (!ptr[num])
		{
			while (num > 0)
			{
				free(ptr[num - 1]);
				num--;
			}
			return (0);
		}
		while (*s == c)
			s++;
		s += aux_len(s, c);
		num++;
	}
	return (1);
}

static unsigned long	aux_numarray(char const *s, char c)
{
	unsigned long	obj;
	unsigned long	counter;

	if (s[0] != c && s[0] != 0)
		obj = 1;
	else
		obj = 0;
	counter = 0;
	while (counter < ft_strlen(s))
	{
		if (s[counter] == c && s[counter + 1] != c && s[counter + 1] != '\0')
			obj++;
		counter++;
	}
	return (obj);
}

static void	aux_fill_malloc(char **ptr, const char *s, char c)
{
	unsigned long	i;
	unsigned long	j;
	const char		*temp;

	i = 0;
	j = 0;
	temp = s;
	while (i < aux_numarray(temp, c))
	{
		while (*s == c)
			s++;
		while (*s && *s != c)
		{
			ptr[i][j] = *s;
			j++;
			s++;
		}
		while (*s == c)
			s++;
		ptr[i][j] = '\0';
		j = 0;
		i++;
	}
}

static unsigned long	aux_len(const char *s, char c)
{
	unsigned long	counter;

	counter = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{	
		counter++;
		s++;
	}
	return (counter);
}
