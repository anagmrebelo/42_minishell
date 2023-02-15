/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:29:21 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/10 17:04:40 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include "free.h"

static void	aux_heredoc(t_master *master, t_token *token, char *line, int fd)
{
	if (line)
		free(line);
	close(fd);
	if (!g_glbl.g_ctrlc)
	{
		free(token->str);
		token->str = ft_strdup(".hdoc");
		if (!token->str)
			clean_free(master, 1);
	}
}

static void	handle_heredoc(t_token *token, char *limit, t_master *master)
{
	int		fd;
	char	*line;

	fd = open(".hdoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		clean_free(master, 1);
	init_signal(2, master->env);
	while (1)
	{
		line = readline("> ");
		if (line == 0)
			break ;
		if (ft_strcmp(line, limit) == 0)
			break ;
		ft_putendl_fd(line, fd);
		if (!token->here)
			line = heredoc_update(line, NULL, master);
	}
	if (g_glbl.g_ctrlc == 1)
		return ;
	else
		aux_heredoc(master, token, line, fd);
	g_glbl.g_ctrlc = 0;
}

/**
 * Checks the line for heredoc
*/
_Bool	check_heredoc(t_master *master)
{
	t_token	*token;

	token = master->token_list;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			handle_heredoc(token, token->str, master);
			if (ft_strcmp(token->str, ".hdoc"))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
