#include "../../../includes/minishell.h"

int	no_such_file_or_directory(int fd_out_save, int error_check, char *str)
{
	int	zero;

	zero = 0;
	if (error_check != zero)
	{
		ft_putstr_fd("minishell: cd: ", fd_out_save);
		ft_putstr_fd(str, fd_out_save);
		ft_putstr_fd(": No such file or directory\n", fd_out_save);
		g_exit_status = 1;
		return (g_exit_status);
	}
	g_exit_status = 0;
	return (g_exit_status);
}

static void	cd_tilde_home(t_inst *inst)
{
	int		error_check_int;
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
		(error_exit(inst->fd_out_save, -5));
	else
	{
		error_check_int = chdir(home_value);
		no_such_file_or_directory(inst->fd_out_save,
			  error_check_int, home_value);
	}
}

static int	cd_home(t_inst *inst)
{
	int		error_check_int;
	char	*home_value;

	home_value = ft_get_env_value("HOME", inst->env_head);
	if (home_value == NULL)
		ft_putstr_fd("minishell: cd: HOME not set\n", inst->fd_out_save);
	else
	{
		error_check_int = chdir(home_value);
		return (no_such_file_or_directory(inst->fd_out_save,
				  error_check_int, home_value));
	}
	return (0);
}

static char	*check_tilde_slash_path(t_inst *inst)
{
	t_tkn	*tkn;
	int		error_check_int;
	char	*hold_str_for_me;
	char	*home_value;

	tkn = *(inst->tkn_head);
	home_value = getenv("HOME");
	if (home_value == NULL)
		(error_exit(inst->fd_out_save, -5));
	else
	{
		if (tkn->args[1][0] == '~' && tkn->args[1][1] == '/')
		{
			hold_str_for_me = ft_strjoin(home_value, &tkn->args[1][1]);
			free(tkn->args[1]);
			tkn->args[1] = ft_strdup(hold_str_for_me);
			free(hold_str_for_me);
		}
		error_check_int = chdir(tkn->args[1]);
		if (error_check_int != 0)
			return (NULL);
	}
	return (tkn->args[1]);
}

int	cd(t_inst *inst, char *arg)
{
	int		error_check;

	error_check = update_old_pwd(inst);
	if (error_check == 1)
		return (g_exit_status);
	if (arg == NULL)
		cd_home(inst);
	else if (check_arg(inst, arg) == 0 && arg[0] != '~')
		cd_somewhere(inst);
	else if (check_arg(inst, "~") == 0 || check_arg(inst, "~/") == 0)
		cd_tilde_home(inst);
	else if (check_tilde_slash_path(inst) != NULL && ft_strlen(arg) > 1)
	{
		error_check = chdir(check_tilde_slash_path(inst));
		no_such_file_or_directory(inst->fd_out_save,
			  error_check, check_tilde_slash_path(inst));
	}
	else
		cd_else(inst);
	update_pwd(inst);
	return (g_exit_status);
}
