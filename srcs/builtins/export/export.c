/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:38:38 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/10 17:51:29 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "builtins.h"
#include "env.h"
#include "free.h"

static	void	update_var(t_env *env, char *title, char *str, t_master *master)
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

static int	only_export(t_master *master)
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

// static void
// 	update_concat(t_env *env, char *title, char *value, t_master *master)
// {
// 	char	*tmp;

// 	while (env != NULL)
// 	{
// 		if (ft_strcmp(title, env->title) == 0)
// 		{
// 			tmp = join_double_free(env->value, value);
// 			env->value = tmp;
// 			free (title);
// 			if (!tmp)
// 			{
// 				free_aux_master(value, title, NULL, master);
// 				break ;
// 			}
// 			break ;
// 		}
// 		env = env->next;
// 	}
// }

// int	concat_var(t_master *master, char *str)
// {
// 	char	*title;
// 	char	*value;

// 	title = get_title(str, master);
// 	value = get_value(str, master);
// 	if (find_in_env(master->env, title))
// 		update_concat(master->env, title, value, master);
// 	else
// 		add_to_env(title, value, master);
// 	return (0);
// }

static int	do_export(t_master *master, char *str)
{
	int		rtrn;
	char	*title;
	int		check;

	rtrn = 0;
	check = var_title_check(str);
	if (check == 1)
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
	else if (check == 2)
		concat_var(master, str);
	else
	{
		print_export_error(str);
		rtrn = 1;
	}
	return (rtrn);
}

void	add_to_env(char *title, char *value, t_master *master)
{
	t_env	*new;

	new = new_env(title, value, master);
	if (!new)
		free_aux_master(title, value, NULL, master);
	add_back(master->env, new);
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
