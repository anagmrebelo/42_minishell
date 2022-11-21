/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:37:57 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/20 18:39:27 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_list_tokens(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d: %s  -> type: %d\n", i, list->str, list->type);
		list = list->next;
		i++;
	}
}

void	print_pipes(t_master *master)
{
	t_pipe *temp;
	t_token *token;
	int		i;

	i = 1;
	temp = master->pipes_list;
	while(temp)
	{
		printf("PIPE %d:\n", i);
		printf("ARGS:");
		token = temp->args;
		while(token)
		{
			printf("%s + ", token->str);
			token = token->next;
		}
		printf("\n");
		printf("INPUTS:");
		token = temp->inputs;
		while(token)
		{
			printf("%s + ", token->str);
			token = token->next;
		}
		printf("\n");
		printf("OUTPUTS:");
		token = temp->outputs;
		while(token)
		{
			printf("%s + ", token->str);
			token = token->next;
		}
		printf("\n");
		printf("\n");
		temp = temp->next;
		i++;
	}
	return ;
}
