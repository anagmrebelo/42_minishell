/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:42:09 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:53:17 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

int		command_separation(t_master *master);
void	add_to_command(t_token *member, t_token **list, t_master *master);
void	del_update(t_token *new);
void	free_fail_exec(char *command, char **path, char **env);
void	free_line(t_master *master);
void	free_commands(t_master *master);
_Bool	parsing(t_master *master);
void	quotes_update(t_token *new, t_master *master);
_Bool	check_quotes(char *line);
void	clean_tokens(t_master *master);
void	free_token_list(t_token *ls);
void	add_list(t_master *list, t_token *item);
t_token	*last_token(t_token *token);
char	**token_to_array(t_token *token, t_master *master);
void	add_type(t_token *new);
_Bool	check_syntax(t_master *master);
void	add_types_redir(t_master *master);


#endif
