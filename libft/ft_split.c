/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:15:36 by mrollo            #+#    #+#             */
/*   Updated: 2022/01/28 16:25:12 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || !s[i + 1]) && s[i] != c)
		{
			count++;
		}
		i++;
	}
	return (count);
}

static int	ft_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		len_ptr;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	len_ptr = ft_count_words(s, c);
	ptr = (char **)ft_calloc((len_ptr + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	while (j < len_ptr)
	{
		while (s[i] == c)
			i++;
		len = ft_len(&s[i], c);
		ptr[j] = ft_substr(s, i, len);
		i = i + len;
		j++;
	}
	return (ptr);
}
