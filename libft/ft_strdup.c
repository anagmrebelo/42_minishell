/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:42:05 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/09 13:36:24 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*ptr;
	unsigned long	counter;

	counter = 0;
	ptr = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (counter <= ft_strlen(s1))
	{
		ptr[counter] = s1[counter];
		counter++;
	}
	return (ptr);
}
