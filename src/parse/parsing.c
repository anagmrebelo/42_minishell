/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:24:30 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/05 11:00:21 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 * Transforms char * line from readline into tokens
*/
_Bool	parsing(char *line, t_master *master)
{
	int	i;

	i = 0;
	if (!check_quotes(line))
	{
		print_error("minishell", NULL, "syntax error\n");
		g_error = 258;
		return (0);
	}
	while (line[i])
		i += tokenize(&line[i], master);
	if (check_syntax(master))
	{
		add_types_redir(master);
		clean_tokens(master);
		check_heredoc(master);	//@arebelo check memory leaks
		command_separation(master);
		return (1);
	}
	return (0);
}

/**
 * Returns true if space, tab, pipe or redirs
*/
_Bool	is_delimeter(char c)
{
	if (is_space(c) || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

_Bool	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

/**
 * Function that creates token and sets i to last char or last space before starting new word
*/
int	tokenize(char *line, t_master *master)
{
	int		i;
	int		quotes;
	t_token	*new;

	i = 0;
	quotes = -1;
	while (line[i] && (!is_delimeter(line[i]) || quotes >= 0))
	{
		if (quotes < 0 && (line[i] == '\'' || line[i] == '\"'))
			quotes = i;
		else if (quotes >= 0 && line[i] == line[quotes])
			quotes = -1;
		i++;
	}
	if (i == 0)
	{
		if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
			i++;
		else if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
			i++;
		i++;
	}
	new = new_token(line, i, master);
	if (new)
		add_list(master, new);
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

/**
 * Creates an instance of token (all initialized as zero)
 * Adds the string component of the token
 * Adds type to the token if it is '>' or '>>' or '<' or '<<' or '|'
 * Calls function to convert env variables $ into its value (env_update)
 * Calls function to clean the sring of closed quotes (quotes_update)
*/
t_token	*new_token(char *line, int size, t_master *master)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		clean_free_pipe_read(master, 1);
	new->str = ft_substr(line, 0, size);
	if (!new->str)
	{
		free(new);
		clean_free_pipe_read(master, 1);
	}
	add_type(new);
	env_update(new, master);
	quotes_update(new, master);
	return (new);
}
