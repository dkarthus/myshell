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

int	is_a_directory(t_inst *inst)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (check_cmd(inst, tkn->cmd) == 0)
		printf("minishell: %s: is a directory\n", tkn->cmd);
	return (0);
}

void	real_substitution(t_inst *inst, int check)
{
	char	*home_value;
	char	*hold_str_for_me;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	home_value = getenv("HOME");
	if (home_value == NULL)
		error_exit(-5);
	if (check == 0)
	{
		free(tkn->cmd);
		tkn->cmd = ft_strdup(home_value);
	}
	else if (check == 1)
	{
		free(tkn->cmd);
		tkn->cmd = ft_strjoin(home_value, "/");
	}
	else if (check == 2)
	{
		hold_str_for_me = ft_substr(tkn->cmd, 1, ft_strlen(tkn->cmd) - 1);
		free(tkn->cmd);
		tkn->cmd = ft_strjoin(home_value, hold_str_for_me);
		free(hold_str_for_me);
	}
}

int	substitute_tilde(t_inst *inst, int check)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (check == 0)
		real_substitution(inst, check);
	else if (check == 1)
		real_substitution(inst, check);
	else if (check == 2)
		real_substitution(inst, check);
	if (chdir(tkn->cmd) == 0)
		return (0);
	return (1);
}

int	it_is_a_directory_there(t_inst *inst)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (ft_strncmp(tkn->cmd, "~", ft_strlen(tkn->cmd)) == 0)
		return (substitute_tilde(inst, 0));
	else if (ft_strncmp(tkn->cmd, "~/", ft_strlen(tkn->cmd)) == 0)
		return (substitute_tilde(inst, 1));
	else if (tkn->cmd[0] == '~' && tkn->cmd[1] == '\0')
		return (substitute_tilde(inst, 2));
	else if (ft_strncmp(tkn->cmd, "/", ft_strlen(tkn->cmd)) == 0)
		return (0);
	else if (chdir(tkn->cmd) == 0)
		return (0);
	else if (chdir(tkn->cmd) == -1)
		return (no_such_file_or_directory(0, tkn->cmd));
	return (1);
}

static int	execute_cd(t_inst *inst, t_tkn *tkn)
{
	exit_status = cd(inst, tkn->args[1]);
	return (exit_status);
}

static int	execute_pwd(t_inst *inst)
{
	exit_status = pwd(inst);
	return (exit_status);
}

static int	execute_env(t_inst *inst)
{
	exit_status = env(inst);
	return (exit_status);
}

static int	execute_unset(t_inst *inst, t_tkn *tkn)
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

int	execute_no_such_file_or_directory_without_cd(t_tkn *tkn)
{
	exit_status = no_such_file_or_directory_1(1, tkn->cmd);
	return (exit_status);
}

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
