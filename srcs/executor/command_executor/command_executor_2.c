#include "../../../includes/minishell.h"

int	execute_unset(t_inst *inst, t_tkn *tkn)
{
	g_exit_status = unset(inst, tkn->args);
	return (g_exit_status);
}

int	execute_export(t_inst *inst, t_tkn *tkn)
{
	g_exit_status = export(inst, tkn->args);
	return (g_exit_status);
}

int	execute_echo(t_tkn *tkn)
{
	g_exit_status = echo(tkn->args);
	return (g_exit_status);
}

int	execute_exit(int fd_out_save, t_tkn *tkn)
{
	g_exit_status = our_exit(fd_out_save, tkn->args);
	return (g_exit_status);
}
