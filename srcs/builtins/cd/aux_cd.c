/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:31:05 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/10 17:51:20 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "free.h"
#include "env.h"
#include "builtins.h"
#include "utils.h"

static void	updt_env_var(t_env *env, char *title, char *value, t_master *master)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->title, title) == 0)
		{
			free (env->value);
			env->value = ft_strdup(value);
			if (!env->value)
				clean_free(master, 1);
			return ;
		}
		env = env->next;
	}
}

int	change_dir(char *arg, char *oldpwd, t_env *env, t_master *master)
{
	if (!arg)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(arg) == 0)
	{
		update_env(oldpwd, env, master);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		if (access(arg, F_OK) == -1)
			ft_putendl_fd("No such file or directory", 2);
		else if (access(arg, R_OK) == -1)
			ft_putendl_fd("Permission denied", 2);
		else
			ft_putendl_fd("Not a directory", 2);
		return (1);
	}
}

void	update_oldpwd(char *oldpwd, t_env *env, t_master *master)
{
	t_env	*aux;
	char	*value;

	aux = env;
	if (find_in_env(aux, "PWD"))
	{
		value = get_env_value("PWD", env);
		if (find_in_env(aux, "OLDPWD"))
			updt_env_var(env, "OLDPWD", value, master);
		else
			add_to_env(ft_strdup("OLDPWD"), ft_strdup(value), master);
	}
	else
		add_to_env(ft_strdup("OLDPWD"), ft_strdup(oldpwd), master);
}

int	update_pwd(t_env *env, t_master *master)
{
	char	*pwd;

	pwd = malloc(4097 * sizeof(char));
	if (!pwd)
		clean_free(master, 1);
	if (getcwd(pwd, 4097) == NULL)
	{
		free (pwd);
		clean_free(master, 1);
	}
	while (env != NULL)
	{
		if (ft_strcmp("PWD", env->title) == 0)
		{
			free (env->value);
			env->value = ft_strdup(pwd);
			if (!env->value)
				free_aux_master(pwd, NULL, NULL, master);
			break ;
		}
		else
			env = env->next;
	}
	free (pwd);
	return (0);
}
