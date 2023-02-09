/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:14:06 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:49:42 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "minishell.h"

char	*remove_dollar(char *str, t_master *master);
_Bool	ok(char c);
char	*create_str(char *str, t_env *temp, t_master *master);
char	*find_var(char *str, t_master *master, int pos, char *full_line);
void	home_update(t_master *master);
char	*env_update(char *read, t_master *master, char *line);
_Bool	aux5_env(char *read, int *c);

#endif
