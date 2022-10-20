#include "../../include/minishell.h"

char    *join_double_free(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *new;


    if (!s1)
    {
        s1 = malloc(sizeof(char) * (1 + 1));
		s1[0] = '\0';
    }
	new = NULL;
   	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!new)
        return (0);
    i = -1;
    while (s1[++i])
        new[i] = s1[i];
    j = -1;
    while (s2[++j])
        new[i + j] = s2[j];
    new[i + j] = '\0';
    free(s1);
	free(s2);
    return (new);
}

void	env_update(t_token *new)
{
	int		i;
	int		j;
	char	*line;

	if (ft_strrchr(new->str, '$') == NULL)
		return ;	
	i = 0;
	j = 0;
	line = NULL;
	while (new->str[i])
	{
		if(new->str[i] == '$' && new->str[i + 1])
		{
			line = join_double_free(line, ft_substr(new->str, j, i - j));
			j = ++i;
			while(new->str[i] && new->str[i] != ' ' && (new->str[i] != '$' || !new->str[i + 1]))
			 	i++;
			line = join_double_free(line, ft_substr(new->str, j, i - j));
			j = i--;
		}
		i++;
	}
	free(new->str);
	new->str = line;
}