/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:53:00 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/01 16:34:14 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_shlvl(t_master *master)
{
	t_env	*new;
	char	*title;
	char	*value;

	title = ft_strdup("SHLVL"); //PREOTEGER
	value = ft_strdup("1"); // PROTEGER
	new = new_env(title, value, master); // PROTEGER
	add_back(master->env, new);
}

void	create_usr_bin(t_master *master)
{
	t_env	*new;
	char	*title;
	char	*value;

	title = ft_strdup("_"); //PROTEGER
	value = ft_strdup("/usr/bin/env"); //PROTEGER
	new = new_env(title, value, master); //PROTEGER
	add_back(master->env, new);
}

void	create_path(t_master *master)
{
	t_env	*new;
	char	*title;
	char	*value;

	title = ft_strdup("PATH"); //PROTEGER
	value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."); //PROTGER
	new = new_env(title, value, master); //PROTEGER
	add_back(master->env, new);
}

int	default_env(t_master *master)
{
	t_env	*env;
	char	*pwd;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		clean_free(master, 1);
	master->env = env;
	pwd = malloc(4097 * sizeof(char));
	if (!pwd)
		return (1); //CLEAN_FREE?
	if (getcwd(pwd, 4097) == NULL)
		return (1); // CLEAN_FREE?
	env->title = ft_strdup("PWD"); // PROTEGER
	env->value = ft_strdup(pwd); // PROTEGER
	create_shlvl(master);
	create_path(master);
	create_usr_bin(master);
	return (0);
}
