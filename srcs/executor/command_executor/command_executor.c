#include "../../../includes/minishell.h"

static int	while_for_command_executor(t_inst *inst, t_tkn *tkn)
{
	while (tkn)
	{
		if (check_cmd(tkn, "cd") == 0)
			return (execute_cd(inst, tkn));
		else if (check_pwd(tkn) == 0)
			return (execute_pwd(inst));
		else if (check_env(tkn) == 0)
			return (execute_env(inst));
		else if (check_cmd(tkn, "unset") == 0)
			return (execute_unset(inst, tkn));
		else if (check_cmd(tkn, "export") == 0)
			return (execute_export(inst, tkn));
		else if (check_cmd(tkn, "echo") == 0)
			return (execute_echo(tkn));
		else if (check_cmd(tkn, "exit") == 0)
			return (execute_exit(inst->fd_out_save, tkn));
		tkn = tkn->next;
	}
	return (-1);
}

int	command_executor(t_inst *inst, t_tkn *tkn)
{
	char	*hold_cmd_for_me;
	int		check;

	hold_cmd_for_me = NULL;
	if (tkn->cmd != NULL)
		hold_cmd_for_me = ft_strdup(tkn->cmd);
	check = while_for_command_executor(inst, tkn);
	free(hold_cmd_for_me);
	if (check != 0)
	{
		if (check == 1)
			return (g_exit_status);
		else
			return (-1);
	}
	return (g_exit_status);
}
