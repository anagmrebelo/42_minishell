/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:29:21 by arebelo           #+#    #+#             */
/*   Updated: 2022/12/02 19:29:26 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    handle_heredoc(t_token *token, char *limit)
{
   int      fd;
   char     *line;

   fd = open(".hdoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
   line = readline("> ");
   while (ft_strcmp(line, limit) != 0)
   {
        ft_putendl_fd(line, fd);
        free (line);
        line = readline("> ");
   }
   free (line);
   close(fd);
   free(token->str);
   token->str = ft_strdup(".hdoc");
}

/**
 * Checks the line for heredoc
*/
void	check_heredoc(t_master *master)
{
	t_token	*token;

	token = master->token_list;
	while (token)
	{
		if (token->type == HEREDOC)
			handle_heredoc(token, token->str);
		token = token->next;
	}
}
