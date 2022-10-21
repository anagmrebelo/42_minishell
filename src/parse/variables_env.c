#include "../../include/minishell.h"

/**
 * Function equivalent to ft_strnjoin however it frees both strings passed as arguments
*/
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


/**
 * Function equivalent to ft_strnjoin however it frees s1
 */
char    *join_free(char *s1, char *s2)
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
    return (new);
}

/**
 * Analyses the str from token and substitutes $ for the environment variables, if there is a match
*/
void	env_update(t_token *new, t_master *master)
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
			line = join_free(line, find_var(ft_substr(new->str, j, i - j), master));
			j = i--;
		}
		i++;
	}
	free(new->str);
	new->str = line;
}

char	*find_var(char * str, t_master *master)
{
	t_list	*temp;

	temp = master->env;
	while(temp)
	{
		if(ft_strncmp(str, temp->title, ft_strlen(str)) == 0)
		{
			free(str);
			return (temp->content); 
		}
		temp = temp->next;
	}
	free(str);
	return (NULL);
}