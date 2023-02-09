/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:05:15 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 15:02:03 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * Function that deletes token from list and updates next and prev
*/
static void	delete_token(t_token *token, t_master *master)
{
	if (token->prev)
		token->prev->next = token->next;
	else
		master->token_list = token->next;
	if (token->next)
		token->next->prev = token->prev;
	if (token->str)
		free(token->str);
	free(token);
}

/**
 * Deletes tokens that have an empty str
*/
void	clean_tokens(t_master *master)
{
	t_token	*temp;

	temp = master->token_list;
	while (temp)
	{
		if ((!temp->str || !temp->str[0]) && !temp->no_del)
			delete_token(temp, master);
		temp = temp->next;
	}
}

/**
* Frees memory of a specific token
*/
static void	free_token(t_token *item)
{
	if (item)
	{
		free(item->str);
		item->str = NULL;
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
