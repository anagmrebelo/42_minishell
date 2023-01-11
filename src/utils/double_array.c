#include "../../include/minishell.h"

/**
 * Frees a double pointer
*/
//cambie tabs x espacios por codespaces en el if y while
void	free_double_array(char **table)
{
	int		i;

	i = 0;
    if (!table)
        return ;
    while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

/**
 * Creates a deep copy of a given char**
*/
char	**copy_double_array(char ** src)
{
	size_t	i;
	char 	**cpy;

	i = 0;
	cpy = NULL;
	while(src && src[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while(src[i])
	{
		cpy[i] = ft_strdup(src[i]);
		if(!cpy[i])
		{
			free_double_array(cpy);
			return (NULL);
		}
		i++;
	}
	return (cpy);
}