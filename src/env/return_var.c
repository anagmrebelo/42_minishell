#include "../../include/minishell.h"

/**
 * Function that returns a shallow copy of the value of env variable with the given title
 * Returns null if variable doesn't exist
*/
char	*getvar_value(t_master *master, char *title)
{
    t_env   *env;

    env = master->env;
    while(env)
    {
		if (ft_strcmp(title, env->title) == 0)
			return(env->value);
		env = env->next;
    }
	return (NULL);
}
