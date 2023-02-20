/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:33:37 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/20 12:33:39 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "utils.h"
#include "builtins.h"
#include "env.h"

static void
	update_concat(t_env *env, char *title, char *value, t_master *master)
{
	char	*tmp;

	while (env != NULL)
	{
		if (ft_strcmp(title, env->title) == 0)
		{
			tmp = join_double_free(env->value, value);
			env->value = tmp;
			free (title);
			if (!tmp)
			{
				free_aux_master(value, title, NULL, master);
				break ;
			}
			break ;
		}
		env = env->next;
	}
}

int	concat_var(t_master *master, char *str)
{
	char	*title;
	char	*value;

	title = get_title(str, master);
	value = get_value(str, master);
	if (find_in_env(master->env, title))
		update_concat(master->env, title, value, master);
	else
		add_to_env(title, value, master);
	return (0);
}
