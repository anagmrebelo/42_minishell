/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:16:18 by mrollo            #+#    #+#             */
/*   Updated: 2022/01/28 16:34:52 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	x;
	size_t	count;
	size_t	len_dest;

	i = ft_strlen(src);
	x = ft_strlen(dst);
	len_dest = ft_strlen(dst);
	count = 0;
	if (dstsize < 1)
		return (i + dstsize);
	while (src[count] && len_dest < dstsize - 1)
	{
		dst[len_dest] = src[count];
		count++;
		len_dest++;
	}
	dst[len_dest] = '\0';
	if (dstsize < x)
		return (i + dstsize);
	return (i + x);
}
