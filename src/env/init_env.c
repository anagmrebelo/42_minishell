/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:15:03 by mrollo            #+#    #+#             */
/*   Updated: 2023/01/11 18:56:19 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env *temp;

	temp = env;
    while (temp != NULL)
    {
		ft_putendl_fd(temp->content, 1);
		temp = temp->next;
	}
}

char	*get_title(char *str, t_master *master)
{
	char *aux;
	int len;
	char *title;

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
	char *aux;
	int len;
	char *value;

	aux = ft_strchr(str, '=');
	if (!aux)
		return (NULL);
	len = (aux - str) + 1;
	value = ft_substr(str, len, ft_strlen(str) - len);
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
	t_env *end;

	if (!new)
		env = new;
	else
	{
		end = last_env(env);
		end->next = new;
	}
}

t_env	*new_env(char *content, char *title, char *value)
{
	t_env *new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
		return (NULL);
	new->title = title;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	init_env(t_master *master, char **enviroment)
{
	t_env *env;
	t_env *new;
	int i;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		clean_free(master, 1);
	master->env = env;
	env->content = ft_strdup(enviroment[0]);
	if (!env->content)
		clean_free(master, 1);
	env->title = get_title(enviroment[0], master);
	env->value = get_value(enviroment[0], master);
	env->next = NULL;
	i = 1;
	while (enviroment && enviroment[i])
	{
		new = new_env(enviroment[i], get_title(enviroment[i], master), get_value(enviroment[i], master));
		if (!new)
			clean_free(master, 1);
		add_back(env, new);
		i++;
	}
	return (0);
}
