#include "../../../include/minishell.h"

void	print_export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	equal_check(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '=')
			i++;
		else
			return (0);
	}
	return (1);
}

int	first_check(char *str)
{
	if (str[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(str[0], 2);
		ft_putchar_fd(str[1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putstr_fd("export: usage: export [-fn] ", 2);
		ft_putendl_fd("[name[=value] ...] or export -p", 2);
		return (1);
	}
	return (0);
}

int	var_title_check(char *str)
{
	int		i;
	int		len;
	char	*aux;

	aux = ft_strchr(str, '=');
	if (!aux)
		len = ft_strlen(str);
	else
		len = aux - str;
	if (len == 0)
		return (0);
	if (equal_check(str))
		return (0);
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		i = 1;
		while (i < len)
		{
			if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
			{
				if ((i == (len - 1)) && str[i] == '+')
					return (1);
				return (0);
			}
			else
				i++;
		}
	}
	else
		return (0);
	return (1);
}