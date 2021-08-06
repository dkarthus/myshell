#include "../../../includes/minishell.h"

int	if_for_check_key(char *str)
{
	if (str[0] == '\0')
		return (1);
	else if (str[0] == ';' && str[1] == '\0')
		return (13);
	else if (str[0] == ';' && str[1] != '\0')
		return (14);
	else if (str[0] == '_' && str[1] == '\0')
		return (2);
	else if (str[0] == '_' && str[1] == '=' && str[2] == '\0')
		return (2);
	else if (str[0] == '~' && str[1] == '\0')
		return (3);
	else if (str[0] == '~' && str[1] == '/' && str[2] == '\0')
		return (4);
	else if (str[0] == '~' && str[1] == '/' && str[2] != '\0')
		return (5);
	else if (str[0] == '~' && str[1] == '-' && str[2] == '\0')
		return (6);
	else if (str[0] == '~' && str[1] == '-' && str[2] == '/' && str[3] == '\0')
		return (7);
	else if (str[0] == '~' && str[1] == '-' && str[2] == '/' && str[3] != '\0')
		return (8);
	else if (str[0] == '~' && str[1] == '+' && str[2] == '\0')
		return (9);
	else if (str[0] == '~' && str[1] == '+' && str[2] == '/' && str[3] == '\0')
		return (10);
	return (-1);
}

int	if_for_check_value(char *str)
{
	int	i;

	if (str[0] == '~' && str[1] == '\0')
		return (16);
	else if (str[0] == '~' && str[1] == '/' && str[2] == '\0')
		return (17);
	else if (str[0] == '~' && str[1] == '/' && str[2] != '\0')
		return (18);
	else if (str[0] == '~' && str[1] == '-' && str[2] == '\0')
		return (19);
	else if (str[0] == '~' && str[1] == '-' && str[2] == '/' && str[3] == '\0')
		return (20);
	else if (str[0] == '~' && str[1] == '-' && str[2] == '/' && str[3] != '\0')
		return (21);
	else if (str[0] == '~' && str[1] == '+' && str[2] == '\0')
		return (22);
	else if (str[0] == '~' && str[1] == '+' && str[2] == '/' && str[3] == '\0')
		return (23);
	else if (str[0] == 126 && str[1] == '+' && str[2] == '/' && str[3] != '\0')
		return (24);
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]) != 0 && str[i] != 59)
			i++;
		else
			return (0);
	}
	return (-1);
}

int	if_for_check_key_1(char *str)
{
	unsigned int	i;

	i = 1;
	if (str[0] == 126 && str[1] == '+' && str[2] == '/' && str[3] != '\0')
		return (11);
	else if (str[0] == 35)
		return (12);
	else if (str[0] == 61 && str[1] == '\0')
		return (15);
	else if (str[0] == 61 && str[1] != '\0')
		return (15);
	else if (str[0] == '\0')
		return (1);
	else if (str[0] != '\0' && str[1] == '\0')
	{
		if ((str[0] > 64 && str[0] < 91)
			|| (str[0] > 96 && str[0] < 123)
			|| (str[0] == 95))
			return (0);
		else
			return (1);
	}
	else
	{
		while (str[i] != '\0')
		{
			if ((str[0] > 64 && str[0] < 91)
				|| (str[0] > 96 && str[0] < 123)
				|| (str[0] == 95))
			{
				if ((str[i] > 47 && str[i] < 58)
					|| (str[i] > 64 && str[i] < 91)
					|| (str[i] > 96 && str[i] < 123)
					|| (str[i] == 95))
				{
					i++;
					continue ;
				}
				else
					return (1);
			}
			else
				return (1);
			i++;
		}
	}
	return (0);
}

unsigned int	key(t_u_e *e, char *key)
{
	int	ret;

	if (ft_strchr(key, '=') != NULL)
	{
		ret = if_for_check_key(e->key);
		if (ret != -1)
			return (ret);
		ret = if_for_check_key_1(e->key);
		if (ret == 0)
			return (ret);
		ret = if_for_check_value(e->value);
		if (ret == 0)
			return (ret);
	}
	else
	{
		ret = if_for_check_key(key);
		if (ret != -1)
			return (ret);
		ret = if_for_check_key_1(key);
		if (ret == 0)
			return (ret);
	}
	return (1);
}

