#include "../../../includes/minishell.h"

static int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i = i + 2;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		if (str[i] == '\0')
			return (0);
	}
	return (1);
}

static int	check_n_option(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL && check_n(args[i]) == 0)
		i++;
	if (args[i] != NULL && check_n(args[i]))
		return (i);
	return (0);
}

static void	echo_1(char **args, int n)
{
	int	hold_n_for_me;

	hold_n_for_me = 0;
	if (n > 1)
	{
		hold_n_for_me = n;
		while (args[n] != NULL)
		{
			if (n > hold_n_for_me)
				write(1, " ", 1);
			write(1, args[n], ft_strlen(args[n]));
			n++;
		}
	}
	else if (n == 1)
	{
		while (args[n] != NULL)
		{
			if (n != 1)
				write(1, " ", 1);
			write(1, args[n], ft_strlen(args[n]));
			n++;
		}
		write(1, "\n", 1);
	}
}

int	echo(char **args)
{
	int		n;

	n = 0;
	if (args[1] != NULL)
	{
		if (ft_strncmp(args[1], "#", 1) == 0)
		{
			write(1, "\n", 1);
			return (0);
		}
		n = check_n_option(args);
		if (n == 0)
			return (0);
		if (n != 0)
			echo_1(args, n);
	}
	else if (args[1] == NULL)
		write(1, "\n", 1);
	return (g_exit_status);
}
