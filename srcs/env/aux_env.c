/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:35:18 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/04 14:35:19 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*aux_shlvl(t_master *master, int shlvl)
{
	char	*str;

	if (shlvl < 0)
		str = ft_strdup("0");
	else
		str = ft_itoa(shlvl);
	if (!str)
		clean_free(master, 1);
	return (str);
}

void	update_shlvl(t_master *master)
{
	int		shlvl;
	char	*value;
	t_env	*aux;

	aux = master->env;
	if (find_in_env(master->env, "SHLVL"))
	{
		value = get_env_value("SHLVL", master->env);
		shlvl = ft_atoi(value) + 1;
		while (aux != NULL)
		{
			if (ft_strcmp(aux->title, "SHLVL") == 0)
			{
				free (aux->value);
				aux->value = aux_shlvl(master, shlvl);
				return ;
			}
			aux = aux->next;
		}
	}
	else
		create_shlvl(master);
}

int	env_len(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	find_in_env(t_env *env, char *str)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->title, str) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}



void	var_update(t_master *master)
{
	t_env	*env;

	env = master->env;
	if (find_in_env(env, "_"))
	{
		while (env != NULL)
		{
			if (ft_strcmp(env->title, "_") == 0)
			{
				free (env->value);
				env->value = ft_strdup("/bin/bash");
				if (!env->value)
					clean_free(master, 1);
				break ;
			}
			env = env->next;
		}
	}
}
