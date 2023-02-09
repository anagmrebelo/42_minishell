/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:49:59 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 14:53:46 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	free_double_array(char **table);
char	**copy_double_array(char **src);
char	*join_double_free(char *s1, char *s2);
char	*join_free_s1(char *s1, char *s2);
char	*join_free_s2(char *s1, char *s2);
char	*free_aux_master(char *s1, char *s2, char *s3, t_master *master);
char	*do_non_print(char *a);
char	*undo_non_print(char *a);
_Bool	is_delimeter(char c);
_Bool	is_space(char c);
_Bool	is_dots(char *cmd);

#endif
