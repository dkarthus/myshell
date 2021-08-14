#include "../../../includes/minishell.h"

static int	check_if_there_is_a_numeric_arg(char *arg)
{
	int	i;

	i = 0;
	if ((arg[i] == 45 || arg[i] == 43) && arg[i] != '\0')
		i++;
	if (arg[i] != '\0')
	{
		while (arg[i] > 47 && arg[i] < 58 && arg[i] != '\0')
			i++;
		if (arg[i] == '\0')
			return (0);
		if (!(arg[i] > 47 && arg[i] < 58 && arg[i] == '\0'))
			return (1);
	}
	else if (arg[i] == '\0')
		return (1);
	return (0);
}

static void	exit_numeric_argument_required(int fd_out_save, char *arg)
{
	ft_putstr_fd("minishell: exit: ", fd_out_save);
	ft_putstr_fd(arg, fd_out_save);
	ft_putstr_fd(": numeric argument required\n", fd_out_save);
	exit(255);
}

static void	exit_many_args(int fd_out_save, char *arg)
{
	int	there_is_a_numeric_arg;

	there_is_a_numeric_arg = 0;
	there_is_a_numeric_arg = check_if_there_is_a_numeric_arg(arg);
	if (there_is_a_numeric_arg == 1)
		exit_numeric_argument_required(fd_out_save, arg);
	else if (there_is_a_numeric_arg == 0)
	{
		ft_putstr_fd("minishell: exit: ", fd_out_save);
		ft_putstr_fd(arg, fd_out_save);
		ft_putstr_fd(": too many arguments\n", fd_out_save);
		g_exit_status = 1;
	}
}

static void	exit_one_arg(int fd_out_save, char *arg)
{
	int	there_is_a_numeric_arg;

	there_is_a_numeric_arg = 0;
	there_is_a_numeric_arg = check_if_there_is_a_numeric_arg(arg);
	if (there_is_a_numeric_arg == 1)
		exit_numeric_argument_required(fd_out_save, arg);
	else if (there_is_a_numeric_arg == 0)
	{
		g_exit_status = ft_atoi(arg);
		exit(g_exit_status);
	}
}

int	our_exit(int fd_out_save, char **args)
{
	int	i;

	i = 1;
	ft_putstr_fd("exit\n", 1);
	g_exit_status = 0;
	if (args[1] != NULL)
	{
		while (args[i] != NULL)
			i++;
		i--;
		if (i > 1)
			exit_many_args(fd_out_save, args[1]);
		else if (i == 1)
			exit_one_arg(fd_out_save, args[1]);
	}
	else if (args[1] == NULL)
		exit(0);
	return (g_exit_status);
}
