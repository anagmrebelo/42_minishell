/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:15:03 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/01 16:47:16 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

char	*get_title(char *str, t_master *master)
{
	char	*aux;
	int		len;
	char	*title;

	aux = ft_strchr(str, '=');
	if (!aux)
		len = ft_strlen(str) + 1;
	else
		len = (aux - str) + 1;
	title = ft_substr(str, 0, len - 1);
	if (!title)
		clean_free(master, 1);
	return (title);
}

char	*get_value(char *str, t_master *master)
{
	char	*aux;
	int		len;
	char	*value;
	char	*tmp;

	aux = ft_strchr(str, '=');
	len = (aux - str) + 1;
	value = ft_substr(str, len, ft_strlen(str) - len);
	if (!value)
		free_aux_master(aux, NULL, NULL, master);
	if (ft_strcmp(value, "\\") == 0 || ft_strcmp(value, "$") == 0)
	{
		tmp = join_free_s2("\\", value); //PROTEGER
		return (tmp);
	}
	return (value);
}

t_env	*last_env(t_env *env)
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

	new = ft_calloc(1, sizeof(t_env)); //PROTEGER TITLE Y VALUE?
	if (!new)
		clean_free(master, 1);
	new->title = title;
	new->value = value;
	new->next = NULL;
	return (new);
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

void	update_shlvl(t_master *master)
{
	int		shlvl;
	char	*value;
	t_env 	*aux;

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
				if (shlvl < 0)
					aux->value = ft_strdup("0"); //proteger
				else
					aux->value = ft_itoa(shlvl); //proteger
				return ;	
			}
			aux = aux->next;
		}
	}
	else
		add_to_env(ft_strdup("SHLVL"), ft_strdup("1"), master);
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
				break ;
			}
			env = env->next;
		}
	}
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
		add_to_env(get_title(enviroment[i], master), get_value(enviroment[i], master), master);
		i++;
	}
	update_shlvl(master);
	var_update(master);
	return (0);
}
