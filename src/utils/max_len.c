#include "../../include/minishell.h"
/**
 * Finds the maximum len between name of the variable given by the user and the title of the enviroment variable being tested
*/
unsigned int	find_max_len(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}