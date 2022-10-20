#include "../../include/minishell.h"

void	env_update(t_token *new)
{
	int		i;
	int		j;
	_Bool	is_valid;
	char	*line;

	if (ft_strrchr(new->str, '$') == NULL)
		return ;
	i = 0;
	is_valid = 1;
	while (new->str[i])
	{
		j = i;
		if(new->str[i] == '$' && new->str[i + 1])
		{
			line = strjoin_double_free(line, ft_substr(line, j, i - j));
			j = i++;
			while(new->str[i] && new->str[i] != ' ' && new->str[i] != '$')
				i++;
			if(new->str[i])
				line = strjoin_double_free(line, ft_substr(line, j, i - j));
			i--;
		}
		i++;
	}
}