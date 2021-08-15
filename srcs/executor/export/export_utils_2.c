#include "../../../includes/minishell.h"

static int	while_for_check_key_2(char *str)
{
	unsigned int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[0]) != 0 || str[0] == '_')
		{
			if (ft_isalnum(str[i]) != 0 || str[i] == '_')
			{
				i++;
				continue ;
			}
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

int	if_for_check_key_1(char *str)
{
	int	error_check;

	error_check = 0;
	if (str[0] != '\0' && str[1] == '\0')
	{
		if (ft_isalpha(str[0]) != 0 || str[0] == '_')
			return (0);
		else
			return (1);
	}
	else
	{
		error_check = while_for_check_key_2(str);
		if (error_check != 0)
			return (error_check);
	}
	return (0);
}

void	free_key_and_value(t_u_e *e)
{
	if (e->key != NULL)
		free(e->key);
	if (e->value != NULL)
		free(e->value);
}

void	split_the_line_for_key_and_value(t_u_e *e, int fd_out_save, char *arg)
{
	int		i;

	if (ft_strchr(arg, '=') != NULL)
	{
		i = 0;
		while (arg[i] != '=')
			i++;
		free_key_and_value(e);
		e->key = ft_substr(arg, 0, i);
		if (e->key == NULL)
			error_exit(fd_out_save, -6);
		e->value = ft_substr(arg, i + 1, ft_strlen(arg));
		if (e->value == NULL)
			error_exit(fd_out_save, -6);
	}
}
