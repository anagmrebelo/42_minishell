#include "../../include/minishell.h"
/**
 * Function that checks if all quotes are closed
 * Returns 0 if not closed;
*/
_Bool	check_quotes(char *line)
{
	int		i;
	int		j;
	_Bool	allow_update;	

	allow_update = 1;
	i = 0;
	j = -1;
	while(line[i])
	{
		if(j < 0 && (line[i] == '\'' || line[i] == '\"' ))
		{
			j = i;
			allow_update = 0;
		}
		else if (j >= 0 && line[i] == line[j])
		{
			j = -1;
			allow_update = 1;
		}	
		i++;
	}
	return(allow_update);
}

/**
 * Function that creates a new char* cleaned of quotes 
*/
char	*quotes_clean(t_token *new, t_master *master)
{
	int		i;
	int		j;
	char	*clean;

	i = 0;
	clean = ft_calloc((ft_strlen(new->str) + 1), sizeof(char));
	if (!clean)
		clean_free(master, 1);
	while(new->str[i])
	{
		j = i;
		while(new->str[i] && new->str[i] != '\'' && new->str[i] != '\"')
			i++;
		ft_strlcat1(clean, &new->str[j], ft_strlen(clean) + i - j + 1);
		if(!new->str[i])
			return (clean);
		j = i++;
		while(new->str[i] && new->str[i] != new->str[j])
			i++;
		ft_strlcat1(clean, &new->str[j+1], ft_strlen(clean) + i++ - j);
	}
	return (clean);
}

/**
 * Function that frees initial str of token with quotes and also elimiates excessive memory in char* from quotes_clean
*/
void	quotes_update(t_token *new, t_master *master)
{
	char	*temp;
	
	temp = new->str;
	new->str = quotes_clean(new, master);
	free(temp);
	temp = new->str;
	new->str = ft_strdup(new->str);
	free(temp);
	if(!new->str)
		clean_free(master, 1);
}
