#include "../../../includes/minishell.h"

static int	while_for_command_executor(t_inst *inst, t_tkn *tkn)
{
	while (tkn)
	{
		if (check_cmd(inst, "cd") == 0)
			return (execute_cd(inst, tkn));
		else if (check_pwd(inst) == 0)
			return (execute_pwd(inst));
		else if (check_env(inst) == 0)
			return (execute_env(inst));
		else if (check_cmd(inst, "unset") == 0)
			return (execute_unset(inst, tkn));
		else if (check_cmd(inst, "export") == 0)
			return (execute_export(inst, tkn));
		else if (check_cmd(inst, "echo") == 0)
			return (execute_echo(tkn));
		else if (check_cmd(inst, "exit") == 0)
			return (execute_exit(tkn));
		else if (it_is_a_directory_there(inst) == 0)
			return (execute_is_a_directory(inst));
		else if (it_is_a_directory_there(inst) == 1)
			return (execute_no_such_file_or_directory_without_cd(tkn));
		tkn = tkn->next;
	}
	return (0);
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
		return (-1);
	return (exit_status);
}
