#include "../../../includes/minishell.h"

static int	if_for_check_key(char *str)
{
	if (str[0] == '\0')
		return (1);
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

static int	if_for_check_key_1(char *str)
{
	if (str[0] == 126 && str[1] == '+' && str[2] == '/' && str[3] != '\0')
		return (11);
	else if (str[0] == '#')
		return (12);
	else if (str[0] == ';' && str[1] == '\0')
		return (13);
	else if (str[0] == ';' && str[1] != '\0')
		return (14);
	else if (str[0] == '=' && str[1] == '\0')
		return (15);
	else if (str[0] == '=' && str[1] != '\0')
		return (15);
	else if (str[0] == '\0')
		return (1);
	return (-1);
}

static int	if_for_check_value(char *str)
{
	int	i;

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

static int	else_for_key(char *key)
{
	int	ret;

	if (ft_strchr(key, '=') == NULL)
	{
		ret = if_for_check_key(key);
		if (ret != -1)
			return (ret);
		ret = if_for_check_key_1(key);
		if (ret != -1)
			return (ret);
		ret = if_for_check_key_2(key);
		if (ret == 0)
			return (ret);
	}
	return (-42);
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
		if (ret != -1)
			return (ret);
		ret = if_for_check_key_2(e->key);
		if (ret == 0)
			return (ret);
		ret = if_for_check_value(e->value);
		if (ret == 0)
			return (ret);
	}
	ret = else_for_key(key);
	if (ret != -42)
		return (ret);
	return (1);
}
