/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:29:21 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/20 11:34:00 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include "free.h"

/**
 * if the heredoc is not exited with ctrl + C then it should change the
 * token->str to the file .hdoc
*/
static void	aux_heredoc(t_master *master, t_token *token)
{
	free(token->str);
	token->str = ft_strdup(".hdoc");
	if (!token->str)
		clean_free(master, 1);
}

static void	child_heredoc(int fd, t_token *token, char *limit, t_master *master)
{
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
		if (!token->here)
			line = heredoc_update(line, NULL, master);
		ft_putendl_fd(line, fd);
	}
	if (line)
		free(line);
	if (close(fd) == -1)
		clean_free(master, 1);
	clean_free_no_exit(master);
	if (g_glbl.g_ctrlc == 1)
		exit(1);
	exit(0);
}

static void	handle_heredoc(t_token *token, char *limit, t_master *master)
{
	int		fd;
	pid_t	pid;
	int		code;

	fd = 0;
	pid = fork();
	if (pid < 0)
		clean_free(master, 1);
	if (pid == 0)
		child_heredoc(fd, token, limit, master);
	init_signal(1, master->env);
	if (waitpid(pid, &code, 0) == -1)
		clean_free(master, 1);
	if (WIFEXITED(code) && WEXITSTATUS(code) == 1)
		return ;
	else
		aux_heredoc(master, token);
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
