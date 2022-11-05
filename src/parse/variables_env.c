#include "../../include/minishell.h"
/**
 * Equivalent to ft_strlen but protects against NULL argument
*/
size_t	ft_strlen_null(const char *str)
{
	int	n;
	
	n = 0;
	if(!str)
		return (n);
	while (str[n])
		n++;
	return (n);
}

/**
 * Function equivalent to ft_strnjoin however it frees both strings passed as arguments
*/
char    *join_double_free(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *new;

    if (!s1)
        s1 = ft_calloc(1, sizeof(char));
   	new = (char *)ft_calloc((ft_strlen_null(s1) + ft_strlen_null(s2) + 1), sizeof(char));
    if (!new)
        return (0);
    i = -1;
    while (s1[++i])
        new[i] = s1[i];
    j = -1;
	if(!s2)
	{
		free(s1);
		free(s2);
   		return (new);
	}
    while (s2[++j])
        new[i + j] = s2[j];
    free(s1);
	free(s2);
    return (new);
}


/**
 * Function equivalent to ft_strnjoin however it frees s1
 */
char    *join_free_s1(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *new;

    if (!s1)
        s1 = ft_calloc(1, sizeof(char));
   	new = (char *)ft_calloc((ft_strlen_null(s1) + ft_strlen_null(s2) + 1), sizeof(char));
    if (!new)
        return (0);
    i = -1;
    while (s1[++i])
        new[i] = s1[i];
    j = -1;
	if(!s2)
	{
		free(s1);
   		return (new);
	}
    while (s2[++j])
        new[i + j] = s2[j];
    free(s1);
    return (new);
}

/**
 * Function equivalent to ft_strnjoin however it frees s2
 */
char    *join_free_s2(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *new;

    if (!s1)
        s1 = ft_calloc(1, sizeof(char));
   	new = (char *)ft_calloc((ft_strlen_null(s1) + ft_strlen_null(s2) + 1), sizeof(char));
    if (!new)
        return (0);
    i = -1;
    while (s1[++i])
        new[i] = s1[i];
    j = -1;
	if(!s2)
   		return (new);
    while (s2[++j])
        new[i + j] = s2[j];
    free(s2);
    return (new);
}

_Bool	allowed_symbols(char c)
{
	if(!ft_isalnum(c) && c != '$')
		return (0);
	return (1);
}

/**
 * Analyses the str from token and substitutes $ for the environment variables, if there is a match
 * It only substitutes if after the $ there is an alphanumeric and it is noit between simple quotes
 * If there is $$ it should print bash pid
*/
void	env_update(t_token *new, t_master *master)
{
	int		i;
	int		j;
	char	*line;

	if (ft_strrchr(new->str, '$') == NULL)
		return ;
	i = -1;
	j = 0;
	line = NULL;
	while (new->str[++i])
	{
		if (new->str[i] == '$' && new->str[i + 1] && allowed_symbols(new->str[i + 1])) // Adjust to tabs also
		{
			line = join_double_free(line, ft_substr(new->str, j, i - j));
			j = ++i;
			while (new->str[i] && allowed_symbols(new->str[i]) && new->str[i] != '$')
			 	i++;
			if(j == i)
			{
				line = join_double_free(line, find_var(ft_substr(new->str, j, 1), master, j, new->str));
				j = i + 1;
			}
			else
			{
				line = join_double_free(line, find_var(ft_substr(new->str, j, i - j), master, j, new->str));
				j = i--;
			}
						
		}
	}
	if(j != i)
		line = join_double_free(line, ft_substr(new->str, j, i - j));
	free(new->str);
	new->str = line;
}

/**
 * Determines if $VAR is allowed to be substituted (if between simple quotes it shouldn't); 
 * If it is (allow_update == 1) and searches for variables named *str on the environment and returns its value; returns NULL if it does not find a match
 * returns $VAR if the substitution is not allowed
*/
char	*find_var(char *str, t_master *master, int pos, char *full_line)
{
	t_env	*temp;
	int		i;
	int		j;
	_Bool	allow_update;	

	allow_update = 1;
	i = 0;
	j = -1;
	while(i < pos)
	{
		if(j < 0 && (full_line[i] == '\'' || full_line[i] == '\"' ))
		{
			j = i;
			if (full_line[i] == '\'')
				allow_update = 0;
		}
		else if (j >= 0 && full_line[i] == full_line[j])
		{
			j = -1;
			allow_update = 1;
		}	
		i++;
	}
	if(allow_update)
	{
		if(ft_strncmp("$", str, find_max_len("$", str)) == 0)
		{
			free(str);
			return(ft_itoa(getpid()));	// Change for bash pid	GETPID is not allowed
		}
		temp = master->env;
		while(temp)
		{
			
			if(ft_strncmp(str, temp->title, find_max_len(str, temp->title)) == 0)
			{
				free(str);
				return (ft_strdup(temp->value)); 
			}
			temp = temp->next;
		}
		free(str);
		return (NULL);
	}
	char	*ll;
	ll = ft_strjoin("$", str);
	free(str);
	return (ll);
}
