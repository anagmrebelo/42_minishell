/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:15:03 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/17 12:32:26 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	lst_to_array(t_master *master)
{
	t_list *tmp;
	int		len;
	int		i;

	tmp = master->env;
	i = 0;
	len = env_mem(master->env, master);
	while (i < len)
	{
		master->env_array[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	master->env_array[i] = "\0";
/*	i = 0;
	while (i < len)
	{
		printf("lst_array[%d]: %s\n", i, master->env_array[i]);
		i++;
		}*/
}

void	print_env(t_list *env)
{
	t_list *temp;

	temp = env;
    while (temp != NULL)
    {
        //printf("%s\n", temp->content);
        printf("title \033[1;92m[%s]\n\033[0;39m", temp->title);
		printf("value \033[1;91m[%s]\n\033[0;39m", temp->value);
		temp = temp->next;
	}
}

char	*get_title(char *str)
{
	char *aux;
	int len;
	char *title;

	aux = ft_strchr(str, '=');
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
	len = (aux - str) + 1;
	value = ft_substr(str, len, ft_strlen(str) - len);
	return (value);
}

int	init_env(t_master *master, char **enviroment)
{
	t_list *env;
	t_list *new;
	int i;

	env = malloc(sizeof(t_list));
	master->env = env;
	env->content = enviroment[0];
	env->title = get_title(enviroment[0]);
	env->value = get_value(enviroment[0]);
	env->next = NULL;
	i = 1;
	while (enviroment && enviroment[i])
	{
		new = ft_lstnew(enviroment[i], get_title(enviroment[i]), get_value(enviroment[i]));
		ft_lstadd_back(&env, new);
		i++;
	}
	return (0);
}
