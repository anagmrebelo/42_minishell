#include "minishell.h"

char	*join_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * (1 + 1));
		s1[0] = '\0';
	}
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