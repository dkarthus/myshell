#include "../../includes/minishell.h"
#include "../../includes/error_exit.h"

int	no_such_file_or_directory(int error_check, const char *str)
{
	int	zero;

	zero = 0;
	if (error_check != zero)
	{
		printf("minishell: cd: %s: No such file or directory\n", str);
		return (1);
	}
	return (0);
}

char	*check_tilde_minus_path(t_inst *inst)
{
	t_tkn	*tkn;
	int		error_check_int;
	char	*hold_str_for_me;
	char	*old_pwd;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
		no_such_file_or_directory(error_check_int, tkn->args[1]);
	else
	{
		if (tkn->args[1][0] == '~' && tkn->args[1][1] == '-' && tkn->args[1][2] == '/' && tkn->args[1][3] != '\0')
		{
			hold_str_for_me = ft_strjoin(old_pwd, &tkn->args[1][2]);
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

int	check_arg(t_inst *inst, const char *str)
{
	t_tkn *tkn;
	size_t	len;

	tkn = *(inst->tkn_head);
	len = ft_strlen(str);
	if (ft_strlen(tkn->args[1]) == len
		&& ft_strncmp(tkn->args[1], str, len) == 0)
		return (0);
	else
		return (1);
}

static int	update_2(t_inst *inst, char *old_pwd)
{
	char	dir[2048];
	char	*error_check_p;
	int		error_check_int;

	error_check_p = getcwd(dir, 2048);
	if (error_check_p == NULL)
		return (error_exit(-2));
	old_pwd = ft_strjoin("OLDPWD=", dir);
	if (old_pwd == NULL)
		return (error_exit(-6));
	error_check_int = ft_add_env_elem(old_pwd, inst->env_head);
	if (error_check_int == 0)
		return (error_exit(-3));
	free(old_pwd);
	return (0);
}

static int	update_1(t_inst *inst, char *old_pwd)
{
	char   *error_check_p;
	int   error_check_int;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		error_check_p = getenv("HOME");
		if (error_check_p == NULL)
			return (error_exit(-5));
		else
		{
			old_pwd = ft_strjoin("OLDPWD=", error_check_p);
			error_check_int = ft_add_env_elem(old_pwd, inst->env_head);
			if (error_check_int == 0)
				return (error_exit(-3));
			free(old_pwd);
			return (0);
		}
	}
	return (0);
}

static int	update(t_inst *inst)
{
	int		error_check_int;
	char	*error_check_p;
	char	*old_pwd;

	error_check_int = 0;
	error_check_p = getenv("HOME");
	if (error_check_p == NULL)
		return (error_exit(-5));
	else
	{
		old_pwd = ft_strjoin("OLDPWD=", error_check_p);
		error_check_int = ft_add_env_elem(old_pwd, inst->env_head);
		if (error_check_int == 0)
			return (error_exit(-3));
		free(old_pwd);
		return (0);
	}
}

static int		check_for_tilde_minus(t_inst *inst, char *first_arg)
{
	if (((first_arg != NULL)
	&& ((check_arg(inst, "~-") == 0)
	|| (check_arg(inst, "~-/") == 0))) == 1)
		return (0);
	return (1);
}

static int		check_for_tilde_minus_slash_s(char *first_arg)
{
	if (((first_arg != NULL)
	&& (first_arg[0] == '~')
	&& (first_arg[1] == '-')
	&& (first_arg[2] == '/')
	&& (first_arg[3] != '\0')) == 1)
		return (0);
	return (1);
}

static int	we_just_started_and_no_arguments(char *old_pwd, char *first_arg)
{
	if ((old_pwd == NULL && first_arg == NULL) == 1)
		return (0);
	return (1);
}

int		update_old_pwd(t_inst *inst)
{
	char	*old_pwd;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	old_pwd = NULL;
	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (we_just_started_and_no_arguments(old_pwd, tkn->args[1]) == 0)
	{
		if (update(inst) == 1)
			return (exit_status);
	}
	else if (check_for_tilde_minus(inst, tkn->args[1]) == 0)
		return (update_1(inst, old_pwd));
	else
	{
		if (check_for_tilde_minus_slash_s(tkn->args[1]) == 0)
			return (update_1(inst, old_pwd));
		else
			return (update_2(inst, old_pwd));
	}
	return (0);
}

int		update_pwd(t_inst *inst)
{
	char	dir[2048];
	char 	*error_check_char_p;
	int 	error_check_int;
	char	*pwd;

	error_check_char_p = getcwd(dir, 2048);
	if (error_check_char_p == NULL)
		return (error_exit(-2));
	pwd = ft_strjoin("PWD=", dir);
	if (pwd == NULL)
		return (error_exit(-6));
	error_check_int = ft_add_env_elem(pwd, inst->env_head);
	if (error_check_int == 0)
		return (error_exit(-4));
	free(pwd);
	return (0);
}

int	cd_tilde_home(void)
{
	int		error_check_int;
	char	*home_value;

	error_check_int = 0;
	home_value = getenv("HOME");
	if (home_value == NULL)
		return (error_exit(-5));
	else
	{
		error_check_int = chdir(home_value);
		return (no_such_file_or_directory(error_check_int, home_value));
	}
}

int	cd_home(t_inst *inst)
{
	int		error_check_int;
	char	*home_value;

	home_value = ft_get_env_value("HOME", inst->env_head);
	if (home_value == NULL)
		write(STDOUT_FILENO, "minishell: cd: HOME not set\n", 28);
	else
	{
		error_check_int = chdir(home_value);
		return (no_such_file_or_directory(error_check_int, home_value));
	}
	return (0);
}

char	*check_tilde_slash_path(t_inst *inst)
{
	t_tkn	*tkn;
	int		error_check_int;
	char	*hold_str_for_me;
	char	*home_value;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	home_value = getenv("HOME");
	if (home_value == NULL)
		error_exit(-5);
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


int	check_cmd(t_inst *inst, const char *str)
{
	t_tkn	*tkn;
	size_t	len;

	tkn = *(inst->tkn_head);
	len = ft_strlen(str);
	if (ft_strlen(tkn->cmd) == len
		&& ft_strncmp(tkn->cmd, str, len) == 0)
		return (0);
	else
		return (1);
}

int	cd_tilde_plus(t_inst *inst)
{
	int		error_check_int;
	char	*pwd;

	error_check_int = 0;
	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
		return (no_such_file_or_directory(error_check_int, "~+"));
	else
	{
		error_check_int = chdir(pwd);
		return (no_such_file_or_directory(error_check_int, pwd));
	}
}

int	cd_tilde_minus(t_inst *inst)
{
	int		error_check_int;
	char	*home_value;

	error_check_int = 0;
	home_value = ft_get_env_value("OLDPWD", inst->env_head);
	if (home_value == NULL)
		return (no_such_file_or_directory(error_check_int, "~-"));
	else
	{
		error_check_int = chdir(home_value);
		return (no_such_file_or_directory(error_check_int, home_value));
	}
}

char	*check_tilde_plus_path(t_inst *inst)
{
	t_tkn	*tkn;
	int		error_check_int;
	char	*hold_str_for_me;
	char	*pwd;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
		no_such_file_or_directory(error_check_int, tkn->args[1]);
	else
	{
		if (tkn->args[1][0] == '~' && tkn->args[1][1] == '+' && tkn->args[1][2] == '/')
		{
			hold_str_for_me = ft_strjoin(pwd, &tkn->args[1][2]);
			if (hold_str_for_me == NULL)
				error_exit(-6);
			free(tkn->args[1]);
			tkn->args[1] = ft_strdup(hold_str_for_me);
			if (tkn->args[1] == NULL)
				error_exit(-6);
			free(hold_str_for_me);
		}
		error_check_int = chdir(tkn->args[1]);
		if (error_check_int != 0)
			return (NULL);
	}
	return (tkn->args[1]);
}

int	cd_plus_minus(t_inst *inst)
{
	int		error_check;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (check_arg(inst, "~+") == 0 || check_arg(inst, "~+/") == 0)
	{
		error_check = cd_tilde_plus(inst);
		if (error_check == 1)
			return (error_check);
	}
	else if (check_arg(inst, "~-") == 0 || check_arg(inst, "~-/") == 0)
	{
		error_check = cd_tilde_minus(inst);
		if (error_check == 1)
			return (error_check);
	}
	else if (check_tilde_plus_path(inst) != NULL)
	{
		error_check = chdir(check_tilde_plus_path(inst));
		return (no_such_file_or_directory(error_check, check_tilde_plus_path(inst)));
	}
	else if (check_tilde_minus_path(inst) != NULL)
	{
		error_check = chdir(check_tilde_minus_path(inst));
		return (no_such_file_or_directory(error_check, check_tilde_minus_path(inst)));
	}
	else
		return (1);
	return (0);
}

int	cd_somewhere(t_inst *inst)
{
	int		error_check;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	error_check = chdir(tkn->args[1]);
	return (no_such_file_or_directory(error_check, tkn->args[1]));
}

int	cd(t_inst *inst, char *arg)
{
	int		error_check;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	error_check = 0;
	error_check = update_old_pwd(inst);
	if (error_check == 1)
		return (exit_status);
	if (arg == NULL)
	{
		error_check = cd_home(inst);
		if (error_check == 1)
			return (exit_status);
	}
	else if (check_arg(inst, arg) == 0 && arg[0] != '~')
	{
		error_check = cd_somewhere(inst);
		if (error_check == 1)
			return (exit_status);
	}
	else if (check_arg(inst, "~") == 0 || check_arg(inst, "~/") == 0)
	{
		error_check = cd_tilde_home();
		if (error_check == 1)
			return (exit_status);
	}
	else if (check_tilde_slash_path(inst) != NULL && ft_strlen(arg) > 1)
	{
		error_check = chdir(check_tilde_slash_path(inst));
		return (no_such_file_or_directory(error_check, check_tilde_slash_path(inst)));
	}
	else if (arg != NULL)
	{
		if (cd_plus_minus(inst) == 0)
		{
			error_check = update_pwd(inst);
			if (error_check == 1)
				return (exit_status);
		}
		error_check = cd_somewhere(inst);
		if (error_check == 1)
			return (exit_status);
	}
	error_check = update_pwd(inst);
	if (error_check == 1)
		return (exit_status);
	return (0);
}
