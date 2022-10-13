/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:59:59 by mrollo            #+#    #+#             */
/*   Updated: 2022/01/28 17:28:43 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_clean_atoi(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == '\t')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int				i;
	int				n;
	unsigned int	result;

	n = 1;
	result = 0;
	i = ft_clean_atoi(nptr);
	if (nptr[i] == '-')
	{
		n = n * -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		if (result > 2147483647 && n == 1)
			return (-1);
		if (result > 2147483648 && n == -1)
			return (0);
		i++;
	}
	return (result * n);
}
