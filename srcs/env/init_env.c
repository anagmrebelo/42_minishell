/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:15:03 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/10 17:50:20 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "free.h"
#include "builtins.h"

void	print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		ft_putstr_fd(temp->title, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(temp->value, 1);
		temp = temp->next;
	}
}

static t_env	*last_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_back(t_env *env, t_env *new)
{
	t_env	*end;

	if (!new)
		env = new;
	else
	{
		end = last_env(env);
		end->next = new;
	}
}

t_env	*new_env(char *title, char *value, t_master *master)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		clean_free(master, 1);
	new->title = title;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	init_env(t_master *master, char **enviroment)
{
	t_env	*env;
	int		i;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		clean_free(master, 1);
	master->env = env;
	env->title = get_title(enviroment[0], master);
	env->value = get_value(enviroment[0], master);
	env->next = NULL;
	i = 1;
	while (enviroment && enviroment[i])
	{
		add_to_env(get_title(enviroment[i], master),
			get_value(enviroment[i], master), master);
		i++;
	}
	update_shlvl(master);
	var_update(master);
	return (0);
}
