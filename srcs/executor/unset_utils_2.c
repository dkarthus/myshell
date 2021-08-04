#include "../../includes/minishell.h"

int	if_for_env_name(char *str)
{
	if (str[0] == 59 && str[1] == '\0')
		return (2);
	else if (str[0] == 59 && str[1] != '\0')
		return (0);
	else if (str[0] == 95 && str[1] == '\0')
		return (2);
	else if (str[0] == 95 && str[1] != '\0')
		return (0);
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

int	if_for_env_name_1(char *str)
{
	unsigned int	i;

	i = 1;
	if (str[0] == 126 && str[1] == '+' && str[2] == '/' && str[3] != '\0')
		return (11);
	else if (str[0] == 33 || (str[0] >= 35 && str[0] <= 38)
		 || (str[0] >= 40 && str[0] <= 59) || (str[0] == 61)
		 || (str[0] >= 63 && str[0] <= 64) || (str[0] >= 91 && str[0] <= 94)
		 || (str[0] == 123) || (str[0] == 125))
		return (0);
	while (str[i] != '\0')
	{
		if ((str[i] >= 48 && str[i] <= 57)
			|| (str[i] >= 65 && str[i] <= 90)
			|| (str[i] >= 97 && str[i] <= 122))
			i++;
		else
			return (0);
	}
	return (-1);
}

unsigned int	env_name(char *str)
{
	int	ret;

	ret = 0;
	ret = if_for_env_name(str);
	if (ret != -1)
		return (ret);
	ret = if_for_env_name_1(str);
	if (ret != -1)
		return (ret);
	return (1);
}
