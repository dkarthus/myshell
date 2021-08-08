#include "../../../includes/minishell.h"

int	no_such_file_or_directory_1(int error_check, const char *str)
{
	int	zero;

	zero = 0;
	if (error_check != zero)
	{
		printf("minishell: %s: No such file or directory\n", str);
		return (0);
	}
	return (1);
}

int	execute_cd(t_inst *inst, t_tkn *tkn)
{
	exit_status = cd(inst, tkn->args[1]);
	return (exit_status);
}

int	execute_pwd(t_inst *inst)
{
	exit_status = pwd(inst);
	return (exit_status);
}

int	execute_env(t_inst *inst)
{
	exit_status = env(inst);
	return (exit_status);
}

int	execute_no_such_file_or_directory_without_cd(t_tkn *tkn)
{
	exit_status = no_such_file_or_directory_1(1, tkn->cmd);
	return (exit_status);
}