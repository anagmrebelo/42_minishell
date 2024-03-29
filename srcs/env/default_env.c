/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:53:00 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/10 17:50:46 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "env.h"
#include "builtins.h"
#include "free.h"

static void	create_usr_bin(t_master *master)
{
	char	*title;
	char	*value;

	title = ft_strdup("_");
	value = ft_strdup("/usr/bin/env");
	if (!title || !value)
		free_aux_master(title, value, NULL, master);
	add_to_env(title, value, master);
}

static void	create_path(t_master *master)
{
	char	*title;
	char	*value;

	title = ft_strdup("PATH");
	value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	if (!title || !value)
		free_aux_master(title, value, NULL, master);
	add_to_env(title, value, master);
}

static void	create_pwd(t_master *master)
{
	char	*pwd;
	t_env	*env;

	env = master->env;
	pwd = malloc(4097 * sizeof(char));
	if (!pwd)
		clean_free(master, 1);
	if (getcwd(pwd, 4097) == NULL)
		free_aux_master(pwd, NULL, NULL, master);
	env->title = ft_strdup("PWD");
	env->value = ft_strdup(pwd);
	if (!env->title || !env->value)
		free_aux_master(env->title, env->value, NULL, master);
	env->next = NULL;
}

void	create_shlvl(t_master *master)
{
	char	*title;
	char	*value;

	title = ft_strdup("SHLVL");
	value = ft_strdup("1");
	if (!title || !value)
		free_aux_master(title, value, NULL, master);
	add_to_env(title, value, master);
}

int	default_env(t_master *master)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		clean_free(master, 1);
	master->env = env;
	create_pwd(master);
	create_shlvl(master);
	create_path(master);
	create_usr_bin(master);
	return (0);
}
