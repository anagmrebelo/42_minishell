/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:38:38 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/08 16:32:33 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_to_env(char *title, char *value, t_master *master)
{
	t_env	*new;

	new = new_env(title, value, master);
	if (!new)
		free_aux_master(title, value, NULL, master);
	add_back(master->env, new);
}

void	update_var(t_env *env, char *title, char *str, t_master *master)
{
	char	*value;

	while (env != NULL)
	{
		if (ft_strcmp(title, env->title) == 0)
		{
			value = get_value(str, master);
			if (ft_strchr(str, '='))
				env->value = value;
			else if (!*value)
			{
				free (value);
				break ;
			}
			break ;
		}
		env = env->next;
	}
}

int	only_export(t_master *master)
{
	char	*title;

	if (!find_in_env(master->env, "OLDPWD"))
	{
		title = ft_strdup("OLDPWD");
		if (!title)
			clean_free(master, 1);
		add_to_env(title, NULL, master);
	}
	print_sort_env(master);
	return (0);
}

int	do_export(t_master *master, char *str)
{
	int		rtrn;
	char	*title;

	rtrn = 0;
	if (var_title_check(str))
	{
		title = get_title(str, master);
		if (find_in_env(master->env, title))
		{
			update_var(master->env, title, str, master);
			free (title);
		}
		else
			add_to_env(title, get_value(str, master), master);
	}
	else
	{
		print_export_error(str);
		rtrn = 1;
	}
	return (rtrn);
}

int	ft_export(t_env *env, char **args, t_master *master)
{
	int		i;
	int		rtrn;

	(void) env;
	rtrn = 0;
	if (!args[1])
		return (only_export(master));
	else
	{
		i = 1;
		while (args && args[i])
		{
			if (first_check(args[i]))
			{
				rtrn = 2;
				break ;
			}
			rtrn = do_export(master, args[i]);
			i++;
		}
	}
	return (rtrn);
}
