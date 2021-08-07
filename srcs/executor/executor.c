#include "../../includes/minishell.h"

int		execute_cd(t_inst *inst, t_tkn *tkn)
{
	exit_status = cd(inst, tkn->args[1]);
	return (exit_status);
}

int		execute_pwd(t_inst *inst)
{
	exit_status = pwd(inst);
	return (exit_status);
}

int		execute_env(t_inst *inst)
{
	exit_status = env(inst);
	return (exit_status);
}

int		execute_unset(t_inst *inst, t_tkn *tkn)
{
	exit_status = unset(inst, tkn->args);
	return (exit_status);
}

int		execute_export(t_inst *inst, t_tkn *tkn)
{
	exit_status = export(inst, tkn->args);
	return (exit_status);
}

int		execute_echo(t_tkn *tkn)
{
	exit_status = echo(tkn->args);
	return (exit_status);
}

int		execute_exit(t_tkn *tkn)
{
	exit_status = our_exit(tkn->args);
	return (exit_status);
}

int		execute_is_a_directory(t_inst *inst)
{
	exit_status = is_a_directory(inst);
	return (exit_status);
}

int		execute_no_such_file_or_directory_1(t_tkn *tkn)
{
	exit_status = no_such_file_or_directory_1(1, tkn->cmd);
	return (exit_status);
}

int		your_wish_is_my_command(t_inst *inst, t_tkn *tkn)
{
	char 	*hold_cmd_for_me;

	hold_cmd_for_me = NULL;
	if (tkn->cmd != NULL)
		hold_cmd_for_me = ft_strdup(tkn->cmd);
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
			return (execute_no_such_file_or_directory_1(tkn));
		tkn = tkn->next;
	}
	free(hold_cmd_for_me);
	return (exit_status);
}