/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:04:07 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/10 17:04:00 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "free.h"

static void	sort(char **sort_array, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(sort_array[i], sort_array[j]) > 0)
			{
				tmp = sort_array[i];
				sort_array[i] = sort_array[j];
				sort_array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	*join_for_sort(t_master *master, char *title, char *val, char **ar)
{
	char	*str;

	str = ft_strdup(title);
	if (!str)
		free_array_master(ar, master);
	str = join_free_s1(str, "=\"");
	if (!str)
		free_array_master(ar, master);
	str = join_free_s1(str, val);
	if (!str)
		free_array_master(ar, master);
	str = join_free_s1(str, "\"");
	if (!str)
		free_array_master(ar, master);
	return (str);
}

static char	**sort_env_array(char **sort_array, t_master *master, int len)
{
	int		i;
	char	*str;
	t_env	*env;

	env = master->env;
	i = 0;
	while (i < len)
	{
		if (env->value)
			str = join_for_sort(master, env->title, env->value, sort_array);
		else
		{
			str = ft_strdup(env->title);
			if (!str)
				free_array_master(sort_array, master);
		}
		sort_array[i] = str;
		env = env->next;
		i++;
	}
	sort(sort_array, len);
	return (sort_array);
}

void	print_sort_env(t_master *master)
{
	int		len;
	int		i;
	char	**sort_array;

	len = env_len(master->env);
	sort_array = ft_calloc((len + 1), sizeof(char *));
	if (!sort_array)
		clean_free(master, 1);
	sort_env_array(sort_array, master, len);
	i = 0;
	while (sort_array && sort_array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(sort_array[i], 1);
		i++;
	}
	free_array(sort_array);
}
