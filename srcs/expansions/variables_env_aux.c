/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_env_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:34:33 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:25:36 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

_Bool	aux5_env(char *read, int *c)
{
	return ((read[c[I]] && ok(read[c[I]])
			&& read[c[I]] != '$' && read[c[I]] != '?'));
}
