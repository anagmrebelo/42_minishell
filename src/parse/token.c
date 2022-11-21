/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:40:10 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/20 18:40:56 by arebelo          ###   ########.fr       */
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
* Frees memory of a specific token
*/
void	free_token(t_token *item)
{
	if (item)
	{
		free(item->str);
		free(item);
	}
}

/**
 * Frees the entire list of tokens
*/
void	free_token_list(t_token *ls)
{
	t_token	*list;
	t_token	*temp;

	list = ls;
	while (list)
	{
		temp = list->next;
		free_token(list);
		list = temp;
	}
}
