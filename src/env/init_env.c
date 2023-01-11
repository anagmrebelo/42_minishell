/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:15:03 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/20 13:32:54 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_env(t_env *env)
{
	t_env *temp;

	temp = env;
    while (temp != NULL)
    {
		//ft_putendl_fd(temp->content, 1);
		ft_putstr_fd(temp->title, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(temp->value, 1);
		temp = temp->next;
	}
}

char	*get_title(char *str)
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
	return (title);
}

char	*get_value(char *str)
{
	char *aux;
	int len;
	char *value;

	aux = ft_strchr(str, '=');
	if (!aux)
		return (NULL);
	len = (aux - str) + 1;
	value = ft_substr(str, len, ft_strlen(str) - len);
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
	master->env = env;
	env->content = ft_strdup(enviroment[0]);
	env->title = get_title(enviroment[0]);
	env->value = get_value(enviroment[0]);
	env->next = NULL;
	i = 1;
	while (enviroment && enviroment[i])
	{
		new = new_env(enviroment[i], get_title(enviroment[i]), get_value(enviroment[i]));
		add_back(env, new);
		i++;
	}
	return (0);
}
