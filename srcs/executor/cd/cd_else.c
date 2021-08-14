#include "../../../includes/minishell.h"

int	check_cmd(t_tkn *tkn, const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (ft_strlen(tkn->cmd) == len
		&& ft_strncmp(tkn->cmd, str, len) == 0)
		return (0);
	else
		return (1);
}

static int	cd_tilde_minus(t_inst *inst)
{
	int		error_check_int;
	char	*home_value;

	error_check_int = 0;
	home_value = ft_get_env_value("OLDPWD", inst->env_head);
	if (home_value == NULL)
		return (no_such_file_or_directory(inst->fd_out_save, error_check_int, "~-"));
	else
	{
		error_check_int = chdir(home_value);
		return (no_such_file_or_directory(inst->fd_out_save, error_check_int, home_value));
	}
}

static int	cd_tilde_plus(t_inst *inst)
{
	int		error_check_int;
	char	*pwd;

	error_check_int = 0;
	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
		no_such_file_or_directory(inst->fd_out_save, error_check_int, "~+");
	else
	{
		error_check_int = chdir(pwd);
		no_such_file_or_directory(inst->fd_out_save, error_check_int, pwd);
	}
	return (0);
}

static int	cd_plus_minus(t_inst *inst)
{
	int		error_check;

	if (check_arg(inst, "~+") == 0 || check_arg(inst, "~+/") == 0)
		cd_tilde_plus(inst);
	else if (check_arg(inst, "~-") == 0 || check_arg(inst, "~-/") == 0)
		cd_tilde_minus(inst);
	else if (check_tilde_plus_path(inst) != NULL)
	{
		error_check = chdir(check_tilde_plus_path(inst));
		no_such_file_or_directory(inst->fd_out_save, error_check, check_tilde_plus_path(inst));
	}
	else if (check_tilde_minus_path(inst) != NULL)
	{
		error_check = chdir(check_tilde_minus_path(inst));
		no_such_file_or_directory(inst->fd_out_save, error_check, check_tilde_minus_path(inst));
	}
	else
		return (1);
	return (0);
}

int	cd_else(t_inst *inst)
{
	if (cd_plus_minus(inst) == 0)
		update_pwd(inst);
	else
		cd_somewhere(inst);
	return (0);
}
