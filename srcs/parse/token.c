/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:40:10 by arebelo           #+#    #+#             */
/*   Updated: 2023/01/31 22:25:26 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 * Add token to the back of the list
*/
void	add_list(t_master *master, t_token *item)
{
	t_token	*end;

	end = last_token(master->token_list);
	if (end)
	{
		end->next = item;
		item->prev = end;
	}
	else
		master->token_list = item;
}

/**
 * Returns the last token of the list
*/
t_token	*last_token(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

/**
 * Returns the first token of the list
*/
t_token	*first_token(t_token *token)
{
	while (token && token->prev)
		token = token->prev;
	return (token);
}

/**
 * Converts token list into a char**
*/
char	**token_to_array(t_token *token, t_master *master)
{
	char	**token_array;
	int		len;
	int		i;

	len = list_len(token);
	token_array = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!token_array)
		clean_free(master, 1);
	i = 0;
	while (i < len)
	{
		token_array[i] = ft_strdup(token->str);
		if (!token_array[i])
		{
			free_double_array(token_array);
			clean_free(master, 1);
		}
		token = token->next;
		i++;
	}
	return (token_array);
}

/**
 * Returns the number of char* from a char**
*/
int	list_len(t_token *token)
{
	int		len;

	len = 0;
	while (token != NULL)
	{
		len++;
		token = token->next;
	}
	return (len);
}
