/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:04:07 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/17 17:09:07 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

void	free_env(char **env_array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free (env_array[i]);
		i++;
	}
}

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

void	print_sort_env(char	**env_array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("declare -x ");
		printf("%s\n", env_array[i]);
		i++;
	}
}

void	sort_env(char **env_array, int len)
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
			if (ft_strcmp(env_array[i], env_array[j]) > 0)
			{
				tmp = env_array[i];
				env_array[i] = env_array[j];
				env_array[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_sort_env(env_array, len);
	free_env(env_array, len);
}

void	env_to_export(t_list *env)
{
	int	len;
	char	**env_array;
	char	*str;
	char	*aux;
	t_list *tmp;
	int i;

	len = len_lst(env);
	env_array = (char **)ft_calloc((len + 1), sizeof(char *));
	tmp = env;
	i = 0;
	while (i < len)
	{
		str = ft_strdup(tmp->title);
		aux = str;
		free (str);
		str = ft_strjoin(aux, "=\"");
		free (aux);
		aux = ft_strjoin(str, tmp->value);
		free (str);
		str = ft_strjoin(aux, "\"");
		//printf("str: %s\n", str);
		env_array[i] = str;
		free (str);
		//printf("env: %s\n", env_array[i]);
		i++;
		tmp = tmp->next;
	}
	sort_env(env_array, len);
}
