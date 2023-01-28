/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:04:07 by mrollo            #+#    #+#             */
/*   Updated: 2023/01/26 11:14:30 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sort(char **sort_array, int len)
{
	int i;
	int j;
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

int exist_oldpwd(t_env *env)
{
    while (env != NULL)
    {
        if (ft_strcmp(env->title, "OLDPWD") == 0)
            return (1);
        env = env->next;
    }
    return (0);
}

char    **sort_env_array(char **sort_array, t_env *env, int len)
{
    int i;
    char *str;
    t_env   *aux;

    aux = env;
    i = 0;
    while (i < len)
    {
        if (env->value)
        {
            str = ft_strdup(env->title);
            str = join_free(str, "=\"");
            str = join_free(str, env->value);
            str = join_free(str, "\"");
        }
        else
            str = ft_strdup(env->title);
        sort_array[i] = str;
        env = env->next;
        i++;
    }
    if (!exist_oldpwd(aux))
    {
        sort_array[i] = ft_strdup("OLDPWD");
        len = len + 1;
    }
    sort(sort_array, len);
    return (sort_array);
}


void    print_sort_env(t_env *env)
{
    int len;
    int i;
    char    **sort_array;

    len = env_len(env);
    if (!exist_oldpwd(env))
        sort_array = ft_calloc((len + 2), sizeof(char *));
    else
        sort_array = ft_calloc((len + 1), sizeof(char *));
    sort_env_array(sort_array, env, len);
    i = 0;
    while (sort_array && sort_array[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(sort_array[i], 1);
        i++;
    }
    free_array(sort_array);
}