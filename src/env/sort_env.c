/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:04:07 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/19 15:42:18 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}

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

char    **sort_env_array(char **sort_array, t_env *env, int len)
{
    int i;
    char *str;
    //char *aux;

    i = 0;
    while (i < len)
    {
        str = ft_strdup(env->title);
        str = join_free(str, "=\"");
        str = join_free(str, env->value);
        str = join_free(str, "\"");
        sort_array[i] = str;
        //aux = join_free(str, "=\"");
        // str = join_free(aux, env->value);
        // aux = join_free(str, "\"");
        // sort_array[i] = aux;
        env = env->next;
        i++;
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