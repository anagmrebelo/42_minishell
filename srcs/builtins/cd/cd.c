/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:59:56 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/10 17:51:12 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "free.h"
#include "builtins.h"
#include "utils.h"

static int	manage_cd(t_master *master, char *pwd)
{
	char	*oldpwd;
	int		rtrn;

	oldpwd = get_env_value("OLDPWD", master->env);
	if (!oldpwd)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		rtrn = 1;
	}
	else if (*oldpwd == '\0')
	{
		ft_putchar_fd('\n', 1);
		rtrn = 0;
	}
	else if (!change_dir(oldpwd, pwd, master->env, master))
	{
		ft_putendl_fd(oldpwd, 1);
		rtrn = 0;
	}
	else
		rtrn = 1;
	return (rtrn);
}

void	update_env(char *oldpwd, t_env *env, t_master *master)
{
	update_oldpwd(oldpwd, env, master);
	update_pwd(env, master);
}

char	*get_env_value(char *title, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(title, env->title) == 0)
			return (env->value);
		else
			env = env->next;
	}
	return (NULL);
}

int	ft_cd(t_env *env, char **args, t_master *master)
{
	char	*home_path;
	char	*pwd;
	int		i;

	home_path = get_env_value("HOME", env);
	pwd = malloc(4097 * sizeof(char));
	if (!pwd)
		clean_free(master, 1);
	if (getcwd(pwd, 4097) == NULL)
		free_aux_master(pwd, NULL, NULL, master);
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0
		|| ft_strcmp(args[1], "--") == 0)
		i = change_dir(home_path, pwd, env, master);
	else if (strcmp(args[1], "-") == 0)
		i = manage_cd(master, pwd);
	else
		i = change_dir(args[1], pwd, env, master);
	free (pwd);
	return (i);
}
