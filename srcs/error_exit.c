#include "../includes/minishell.h"

void	str_error(const char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	exit_status = 1;
}

int		error_exit(int err_code)
{
	write(1, "\033[31mError\033[0m\n", 15);
	if (err_code == -1)
		str_error("chdir() returned -1\n");
	else if (err_code == -2)
		str_error("getcwd() returned NULL\n");
	else if (err_code == -3)
		str_error("ft_add_env_value() returned 0\n");
	else if (err_code == -4)
		str_error("ft_add_env_value(pwd, inst->env_head) returned 0\n");
	else if (err_code == -5)
		str_error("getenv(\"HOME\") returned NULL\n");
	else if (err_code == -6)
		str_error("Malloc has failed\n");
	return (exit_status);
}

