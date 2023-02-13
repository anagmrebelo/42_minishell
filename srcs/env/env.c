/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:36:39 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/09 16:01:09 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "free.h"
#include "utils.h"

static char	
	*join_title_value(t_master *master, char *title, char *value, char **ar)
{
	char	*str;

	str = ft_strdup(title);
	if (!str)
		free_array_master(ar, master);
	str = join_free_s1(str, "=");
	if (!str)
		free_array_master(ar, master);
	str = join_free_s1(str, value);
	if (!str)
		free_array_master(ar, master);
	return (str);
}

static char	**fill_array(t_master *master, char **array, int len)
{
	int		i;
	t_env	*env;
	char	*str;

	env = master->env;
	i = 0;
	while (i < len)
	{
		if (env->value)
			str = join_title_value(master, env->title, env->value, array);
		else
		{
			str = ft_strdup(env->title);
			if (!str)
				free_array_master(array, master);
		}
		array[i] = str;
		if (!array[i])
			free_array_master(array, master);
		i++;
		env = env->next;
	}
	return (array);
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
		tmp = join_free_s2("\\", value);
		return (tmp);
	}
	return (value);
}

char	**env_to_array(t_master *master)
{
	char	**array_env;
	int		len;
	t_env	*env;

	env = master->env;
	len = env_len(env);
	array_env = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!array_env)
		clean_free(master, 1);
	array_env = fill_array(master, array_env, len);
	return (array_env);
}
