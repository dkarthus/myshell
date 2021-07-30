#include "../includes/minishell.h"

void	error_exit(t_inst *inst, int err_code)
{
	t_env	*env_head;

	env_head = *(inst->env_head);
	write(1, "\033[31mError\033[0m\n", 15);
	if (err_code == -1)
		write(STDERR_FILENO, "chdir() returned -1\ncould not change "
					   "current working directory\n", 67);
	else if (err_code == -2)
		write(STDERR_FILENO, "getcwd() returned NULL\ncould not get "
					   "current working directory\n", 63);
	else if (err_code == -3)
		write(STDERR_FILENO, "ft_add_env_value(old_pwd, inst->env_head) "
					   "returned 0\ncould not add env variable\n", 80);
	else if (err_code == -4)
		write(STDERR_FILENO, "ft_add_env_value(pwd, inst->env_head) "
							 "returned 0\ncould not add env variable\n", 80);
	else if (err_code == -5)
		write(STDOUT_FILENO, "getenv(\"HOME\") returned NULL\n", 31);
//	ft_free_env(&env_head);
}

