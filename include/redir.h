/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:53:01 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:49:55 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "minishell.h"
# include "parse.h"
# include <unistd.h>

void	init_redirs(t_master *master);
void	init_pipe(t_master *master);
void	close_init_redirs(t_master *master);
void	handle_redirs(t_command *cmd, t_master *master);
void	handle_pipe(t_master *master, t_command *cmd);
void	handle_outputs(t_command *cmd, t_master *master);
void	redir_inputs(t_command *cmd, t_master *master);
void	redir_outputs(t_command *cmd, t_master *master);
_Bool	validate_input(t_token *temp, t_command *cmd, t_master *master);
_Bool	validate_output(char *str, t_command *cmd, t_master *master);
char	*file_new_path(char *str, t_master *master);
void	reset_redirs(t_master *master);

#endif
