#include "../../../includes/minishell.h"

int	no_such_file_or_directory_1(int error_check, const char *str)
{
	int	zero;

	zero = 0;
	if (error_check != zero)
	{
		printf("\033[90mminishell: %s: No such file or directory\033[0m\n", str);
		return (0);
	}
	return (1);
}

int	execute_cd(t_inst *inst, t_tkn *tkn)
{
	g_exit_status = cd(inst, tkn->args[1]);
	return (g_exit_status);
}

int	execute_pwd(t_inst *inst)
{
	g_exit_status = pwd(inst);
	return (g_exit_status);
}

int	execute_env(t_inst *inst)
{
	g_exit_status = env(inst);
	return (g_exit_status);
}

int	execute_no_such_file_or_directory_without_cd(t_tkn *tkn)
{
	g_exit_status = no_such_file_or_directory_1(1, tkn->cmd);
	return (g_exit_status);
}
