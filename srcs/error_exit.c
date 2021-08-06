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
		str_error("chdir() returned -1\ncould not change current working directory\n");
	else if (err_code == -2)
		str_error("getcwd() returned NULL\ncould not get "
				  "current working directory\n");
	else if (err_code == -3)
		str_error("ft_add_env_value(old_pwd, inst->env_head) "
					   "returned 0\ncould not add env variable\n");
	else if (err_code == -4)
		str_error("ft_add_env_value(pwd, inst->env_head)"
							 "returned 0\ncould not add env variable\n");
	else if (err_code == -5)
	{
		write(STDOUT_FILENO, "getenv(\"HOME\") returned NULL\n", 31);
		exit_status = 1;
	}
	else if (err_code == -6)
	{
		write(STDOUT_FILENO, "Malloc in export_env_var)failed\n", 32);
		exit_status = 1;
	}
	return (exit_status);
}

