/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:36:39 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/01 16:37:34 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free (array[i]);
		i++;
	}
	free(array);
}

void	print_array(char **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%s\n", array[i]);
		i++;
	}
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

char	**env_to_array(t_env *env)
{
	char	**array_env;
	char	*str;
	int		i;
	int		len;

	len = env_len(env);
	array_env = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!array_env)
		return (NULL); //CLEAN_FREE
	i = 0;
	while (i < len)
	{
		if (env->value)
		{
			str = ft_strdup(env->title); //PROTEGER
			str = join_free(str, "="); //PROTEGER
			str = join_free(str, env->value); // PROTEGER
		}
		else
			str = ft_strdup(env->title); //PROTEGER
		array_env[i] = str;
		if (!array_env[i])
		{
			free_double_array(array_env);
			return (NULL); //CLEAN_FREE
		}
		i++;
		env = env->next;
	}
	return (array_env);
}
