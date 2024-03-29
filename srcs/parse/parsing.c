/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:24:30 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/20 12:00:06 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include "free.h"
#include "errors.h"
#include "expansions.h"
#include "heredoc.h"

static int	aux_tokenize(char *line, int i)
{
	int		quotes;

	quotes = -1;
	while (line[i] && (!is_delimeter(line[i]) || quotes >= 0))
	{
		if (quotes < 0 && (line[i] == '\'' || line[i] == '\"'))
			quotes = i;
		else if (quotes >= 0 && line[i] == line[quotes])
			quotes = -1;
		i++;
	}
	return (i);
}

/**
 * Creates an instance of token (all initialized as zero)
 * Adds the string component of the token
 * Adds type to the token if it is '>' or '>>' or '<' or '<<' or '|'
 * Calls function to convert env variables $ into its value (env_update)
 * Calls function to clean the sring of closed quotes (quotes_update)
*/
static t_token	*new_token(char *line, int size, t_master *master)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		clean_free(master, 1);
	new->str = ft_substr(line, 0, size);
	if (!new->str)
	{
		free(new);
		clean_free(master, 1);
	}
	add_type(new);
	del_update(new);
	quotes_update(new, master);
	return (new);
}

/**
 * Function that creates token and sets i to last char or last space before
 * starting new word
*/
static int	tokenize(char *line, t_master *master)
{
	int		i;
	t_token	*new;
	char	*temp;

	i = 0;
	temp = line;
	while (is_space(line[i]))
		line++;
	i = aux_tokenize(line, i);
	if (i == 0)
	{
		if ((line[i] == '<' && line[i + 1] && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] && line[i + 1] == '>'))
			i++;
		i++;
	}
	new = new_token(line, i, master);
	if (new)
		add_list(master, new);
	while (line[i] && is_space(line[i]))
		i++;
	return (line + i - temp);
}

static void	syntax_err(void)
{
	print_error("minishell", NULL, "syntax error\n");
	g_glbl.g_error = 258;
}

/**
 * Transforms char * line from readline into tokens
*/
_Bool	parsing(t_master *master)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!check_quotes(master->line))
	{
		syntax_err();
		return (0);
	}
	home_update(master);
	tmp = env_update(master->line, master, NULL);
	if (tmp != master->line)
		free_line(master);
	master->line = tmp;
	while (master->line[i])
		i += tokenize(&master->line[i], master);
	if (check_syntax(master))
	{
		add_types_redir(master);
		clean_tokens(master);
		if (!check_heredoc(master))
			return (0);
		return (command_separation(master));
	}
	return (0);
}
