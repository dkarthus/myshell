#include "../../../includes/minishell.h"

int	execute_unset(t_inst *inst, t_tkn *tkn)
{
	exit_status = unset(inst, tkn->args);
	return (exit_status);
}

int	execute_export(t_inst *inst, t_tkn *tkn)
{
	exit_status = export(inst, tkn->args);
	return (exit_status);
}

int	execute_echo(t_tkn *tkn)
{
	exit_status = echo(tkn->args);
	return (exit_status);
}

int	execute_exit(t_tkn *tkn)
{
	exit_status = our_exit(tkn->args);
	return (exit_status);
}

int	execute_is_a_directory(t_inst *inst)
{
	exit_status = is_a_directory(inst);
	return (exit_status);
}
