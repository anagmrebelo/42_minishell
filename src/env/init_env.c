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
	if (!aux)
		clean_free(master, 1);
	len = (aux - str) + 1;
	value = ft_substr(str, len, ft_strlen(str) - len);
	if (!value)
		clean_free(master, 1);
	if (ft_strcmp(value, "\\") == 0 || ft_strcmp(value, "$") == 0)
	{
		tmp = join_free_s2("\\", value);
		return (tmp);
	}
	if (!value)
		clean_free(master, 1);
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

	new = ft_calloc(1, sizeof(t_env));
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

int	init_env(t_master *master, char **enviroment)
{
	t_env	*env;
	t_env	*new;
	int		i;
	int		shlvl;

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
		new = new_env(get_title(enviroment[i], master), get_value(enviroment[i], master), master);
		if (ft_strcmp(new->title, "SHLVL") == 0)
		{
			shlvl = ft_atoi(new->value) + 1;
			free (new->value);
			if (shlvl < 0)
				new->value = ft_strdup("0");
			else
				new->value = ft_itoa(shlvl);
		}
		if (!new)
			clean_free(master, 1);
		add_back(env, new);
		i++;
	}
	if (!find_in_env(env, "SHLVL"))
		add_to_env(ft_strdup("SHLVL"), ft_strdup("1"), master);
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
	return (0);
}
