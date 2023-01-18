/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:42:05 by mrollo            #+#    #+#             */
/*   Updated: 2023/01/18 18:38:43 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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