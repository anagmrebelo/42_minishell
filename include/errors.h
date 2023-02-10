/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:40:43 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:49:15 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

void	no_file_dir(t_master *master, char *cmd, int exit_code);
void	perm_denied(t_master *master, char *cmd, int exit_code);
void	not_dir(t_master *master, char *cmd, int exit_code);
void	print_error(char *minishell, char *builtin, char *message);
char	*create_message(t_master *master, char *message,
			char *token, char *msg);

#endif
