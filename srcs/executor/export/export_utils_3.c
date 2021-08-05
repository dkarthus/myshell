#include "../../../includes/minishell.h"

int	if_for_export_env_key(char *str)
{
	if (str[0] == 59 && str[1] == '\0')
		return (2);
	else if (str[0] == 59 && str[1] != '\0')
		return (0);
	else if (str[0] == 95 && str[1] == '\0')
		return (2);
	else if (str[0] == 126 && str[1] == '\0')
		return (3);
	else if (str[0] == 126 && str[1] == '/' && str[2] == '\0')
		return (4);
	else if (str[0] == 126 && str[1] == '/' && str[2] != '\0')
		return (5);
	else if (str[0] == 126 && str[1] == '-' && str[2] == '\0')
		return (6);
	else if (str[0] == 126 && str[1] == '-' && str[2] == '/' && str[3] == '\0')
		return (7);
	else if (str[0] == 126 && str[1] == '-' && str[2] == '/' && str[3] != '\0')
		return (8);
	else if (str[0] == 126 && str[1] == '+' && str[2] == '\0')
		return (9);
	else if (str[0] == 126 && str[1] == '+' && str[2] == '/' && str[3] == '\0')
		return (10);
	return (-1);
}

int	if_for_export_env_value(char *str)
{
	if (str[0] == 59 && str[1] == '\0')
		return (2);
	else if (str[0] == 59 && str[1] != '\0')
		return (0);
	else if (str[0] == 95 && str[1] == '\0')
		return (2);
	else if (str[0] == 126 && str[1] == '\0')
		return (3);
	else if (str[0] == 126 && str[1] == '/' && str[2] == '\0')
		return (4);
	else if (str[0] == 126 && str[1] == '/' && str[2] != '\0')
		return (5);
	else if (str[0] == 126 && str[1] == '-' && str[2] == '\0')
		return (6);
	else if (str[0] == 126 && str[1] == '-' && str[2] == '/' && str[3] == '\0')
		return (7);
	else if (str[0] == 126 && str[1] == '-' && str[2] == '/' && str[3] != '\0')
		return (8);
	else if (str[0] == 126 && str[1] == '+' && str[2] == '\0')
		return (9);
	else if (str[0] == 126 && str[1] == '+' && str[2] == '/' && str[3] == '\0')
		return (10);
	return (-1);
}

int	if_for_export_env_key_1(char *str)
{
	unsigned int	i;

	i = 1;
	if (str[0] == 126 && str[1] == '+' && str[2] == '/' && str[3] != '\0')
		return (11);
	else if (str[0] == 35)
		return (12);
	else if (str[0] != '\0' && str[1] == '\0')
	{
		printf("\033[90mchecking the first character now\033[0m\n");
		if ((str[0] > 64 && str[0] < 91)
			|| (str[0] > 96 && str[0] < 123)
			|| (str[0] == 95))
		{
			printf("\033[92mright!\033[0m\n>%s\n", str);
			return (1);
		}
		else
		{
			printf("\033[91mwrong!\033[0m\n>%s\n", str);
			return (0);
		}
	}
	else
	{
		printf("\033[90mchecking the rest of the line now\033[0m\n");
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
				{
					printf("\033[91mwrong!\033[0m\n>%s\n", str);
					return (0);
				}
			}
			else
			{
				printf("\033[91mfirst character is wrong!\033[0m\n>%s\n", str);
				return (0);
			}
			i++;
		}
	}
	return (-1);
}

unsigned int	export_env_var(char *str)
{
	int	ret;
	int i;
	char *key;
	char *value;

	i = 0;
	if (ft_strchr(str, '#') == 0)
	{
		while (str[i] != '=')
			i++;
		key = ft_substr(str, 0, i);
		value = ft_substr(str, i + 1, ft_strlen(str));
		if (key == NULL || value == NULL)
		{

		}
		ret = if_for_export_env_key(key);
		if (ret != -1)
		{
			free(key);
			free(value);
			return (ret);
		}
		ret = if_for_export_env_key_1(key);
		if (ret != -1)
			return (ret);
		ret = if_for_export_env_value(value);
		if (ret != -1)
			return (ret);
		ret = if_for_export_env_value(value);
		if (ret != -1)
			return (ret);
	}
	else
	{
		ret = if_for_export_env_key(str);
		if (ret != -1)
			return (ret);
		ret = if_for_export_env_key_1(str);
		if (ret != -1)
			return (ret);
	}
	return (1);
}