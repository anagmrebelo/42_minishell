#include "../../include/minishell.h"

/**
 * Frees a double pointer
*/
void	free_double_array(char **table)
{
	int		i;

	i = 0;
    if (!table)
        return ;
	while(table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}