/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:02:49 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/09 13:34:21 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*str;
	long int	nb;

	nb = n;
	len = ft_numlen(n);
	str = ft_calloc(1, len + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	if (n < 0)
	{
		nb = nb * -1;
		str[0] = '-';
	}
	while (nb > 0)
	{
		str[--len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (str);
}
