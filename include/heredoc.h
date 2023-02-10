/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:08:26 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:49:49 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

char	*find_here(char *str, t_master *master, int pos, char *full_line);
char	*heredoc_update(char *read, char *line, t_master *master);
_Bool	check_heredoc(t_master *master);

#endif
