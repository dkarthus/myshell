#include "../../includes/minishell.h"
#include "../../includes/error_exit.h"

int		no_such_file_or_directory(int error_check, const char *str)
{
	int	zero;

	zero = 0;
	if (error_check != zero)
	{
		printf("minishell: cd: %s: No such file or directory\n", str);
		return (0);
	}
	return (1);
}

char	*check_tilde_minus_path(t_inst *inst)
{
	t_tkn	*tkn;
	int 	error_check_int;
	char	*hold_str_address_for_me;
	char	*hold_str_for_me;
	char	*old_pwd;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
		no_such_file_or_directory(error_check_int, tkn->args[0]);
	else
	{
		if (tkn->args[0][0] == '~' && tkn->args[0][1] == '-' && tkn->args[0][2] == '/' && tkn->args[0][3] != '\0')
		{
			hold_str_address_for_me = tkn->args[0];
			hold_str_for_me = ft_strjoin(old_pwd, &tkn->args[0][2]);
			free(tkn->args[0]);
			tkn->args[0] = ft_strdup(hold_str_for_me);
			free(hold_str_for_me);
		}
		error_check_int = chdir(tkn->args[0]);
		if (error_check_int != 0)
			return (NULL);
	}
	return (tkn->args[0]);
}

int		check_arg(t_inst *inst, const char *str)
{
	t_tkn *tkn;
	size_t	len;

	tkn = *(inst->tkn_head);
	len = ft_strlen(str);
	if (ft_strlen(tkn->args[0]) == len
		&& ft_strncmp(tkn->args[0], str, len) == 0)
		return (0);
	else
		return (1);
}

void 	if_for_updating_old_pwd(t_inst *inst)
{
	char   *error_check_char_p;
	int   error_check_int;
	char  *old_pwd;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		error_check_char_p = getenv("HOME");
		if (error_check_char_p == NULL)
			error_exit(-5);
		else
		{
			old_pwd = ft_strjoin("OLDPWD=", error_check_char_p);
			error_check_int = ft_add_env_elem(old_pwd, inst->env_head);
			if (error_check_int == 0)
				error_exit(-3);
			free(old_pwd);
			return ;
		}
	}
}

void	update_old_pwd(t_inst *inst)
{
	char  dir[2048];
	char   *error_check_char_p;
	int   error_check_int;
	char  *old_pwd;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL && tkn->args[0] == NULL)
	{
		error_check_char_p = getenv("HOME");
		if (error_check_char_p == NULL)
			error_exit(-5);
		else
		{
			old_pwd = ft_strjoin("OLDPWD=", error_check_char_p);
			error_check_int = ft_add_env_elem(old_pwd, inst->env_head);
			if (error_check_int == 0)
				error_exit(-3);
			free(old_pwd);
			return ;
		}
	}
	else if (tkn->args[0] != NULL && ((check_arg(inst, "~-") == 0 || check_arg(inst, "~-/") == 0)))
		if_for_updating_old_pwd(inst);
	else
	{
		if (tkn->args[0] != NULL && tkn->args[0][0] == '~' && tkn->args[0][1] == '-' && tkn->args[0][2] == '/' && tkn->args[0][3] != '\0')
			if_for_updating_old_pwd(inst);
		else
		{
			error_check_char_p = getcwd(dir, 2048);
			if (error_check_char_p == NULL)
				error_exit(-2);
			old_pwd = ft_strjoin("OLDPWD=", dir);
			error_check_int = ft_add_env_elem(old_pwd, inst->env_head);
			if (error_check_int == 0)
				error_exit(-3);
			free(old_pwd);
			return;
		}
	}
}

int		update_pwd(t_inst *inst)
{
	char	dir[2048];
	char 	*error_check_char_p;
	int 	error_check_int;
	char	*pwd;

	error_check_char_p = getcwd(dir, 2048);
	if (error_check_char_p == NULL)
		error_exit(-2);
	pwd = ft_strjoin("PWD=", dir);
	error_check_int = ft_add_env_elem(pwd, inst->env_head);
	if (error_check_int == 0)
		error_exit(-4);
	free(pwd);
	return (0);
}


int		no_such_file_or_directory_1(int error_check, const char *str)
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

void	cd_tilde_home(void)
{
	int		error_check_int;
	char	*home_value;

	error_check_int = 0;
	home_value = getenv("HOME");
	if (home_value == NULL)
		error_exit(-5);
	else
	{
		error_check_int = chdir(home_value);
		no_such_file_or_directory(error_check_int, home_value);
	}
	return ;
}

void	cd_home(t_inst *inst)
{
	int		error_check_int;
	char	*home_value;

	home_value = ft_get_env_value("HOME", inst->env_head);
	if (home_value == NULL)
		write(STDOUT_FILENO, "minishell: cd: HOME not set\n", 28);
	else
	{
		error_check_int = chdir(home_value);
		no_such_file_or_directory(error_check_int, home_value);
	}
}

char	*check_tilde_slash_path(t_inst *inst)
{
	t_tkn	*tkn;
	int 	error_check_int;
	char	*hold_str_address_for_me;
	char	*hold_str_for_me;
	char	*home_value;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	home_value = getenv("HOME");
	if (home_value == NULL)
		error_exit(-5);
	else
	{
		if (tkn->args[0][0] == '~' && tkn->args[0][1] == '/')
		{
			hold_str_address_for_me = tkn->args[0];
			hold_str_for_me = ft_strjoin(home_value, &tkn->args[0][1]);
			free(tkn->args[0]);
			tkn->args[0] = ft_strdup(hold_str_for_me);
			free(hold_str_for_me);
		}
		error_check_int = chdir(tkn->args[0]);
		if (error_check_int != 0)
			return (NULL);
	}
	return (tkn->args[0]);
}


int		check_cmd(t_inst *inst, const char *str)
{
	t_tkn *tkn;
	size_t	len;

	tkn = *(inst->tkn_head);
	len = ft_strlen(str);
	if (ft_strlen(tkn->cmd) == len
		&& ft_strncmp(tkn->cmd, str, len) == 0)
		return (0);
	else
		return (1);
}

void	cd_tilde_plus(t_inst *inst)
{
	int		error_check_int;
	char	*pwd;

	error_check_int = 0;
	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
		no_such_file_or_directory(error_check_int, "~+");
	else
	{
		error_check_int = chdir(pwd);
		no_such_file_or_directory(error_check_int, pwd);
	}
	return ;
}

void	cd_tilde_minus(t_inst *inst)
{
	int		error_check_int;
	char	*home_value;

	error_check_int = 0;
	home_value = ft_get_env_value("OLDPWD", inst->env_head);
	if (home_value == NULL)
		no_such_file_or_directory(error_check_int, "~-");
	else
	{
		error_check_int = chdir(home_value);
		no_such_file_or_directory(error_check_int, home_value);
	}
	return ;
}

char	*check_tilde_plus_path(t_inst *inst)
{
	t_tkn	*tkn;
	int 	error_check_int;
	char	*hold_str_address_for_me;
	char	*hold_str_for_me;
	char	*pwd;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
		no_such_file_or_directory(error_check_int, tkn->args[0]);
	else
	{
		if (tkn->args[0][0] == '~' && tkn->args[0][1] == '+' && tkn->args[0][2] == '/')
		{
			hold_str_address_for_me = tkn->args[0];
			hold_str_for_me = ft_strjoin(pwd, &tkn->args[0][2]);
			free(tkn->args[0]);
			tkn->args[0] = ft_strdup(hold_str_for_me);
			free(hold_str_for_me);
		}
		error_check_int = chdir(tkn->args[0]);
		if (error_check_int != 0)
			return (NULL);
	}
	return (tkn->args[0]);
}

int		cd_plus_minus(t_inst *inst)
{
	int		error_check;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (check_arg(inst, "~+") == 0 || check_arg(inst, "~+/") == 0)
		cd_tilde_plus(inst);
	else if (check_arg(inst, "~-") == 0 || check_arg(inst, "~-/") == 0)
		cd_tilde_minus(inst);
	else if (check_tilde_plus_path(inst) != NULL)
	{
		error_check = chdir(check_tilde_plus_path(inst));
		no_such_file_or_directory(error_check, check_tilde_plus_path(inst));
	}
	else if (check_tilde_minus_path(inst) != NULL)
	{
		error_check = chdir(check_tilde_minus_path(inst));
		no_such_file_or_directory(error_check, check_tilde_minus_path(inst));
	}
	else
		return (1);
	return (0);
}

void	cd_somewhere(t_inst *inst)
{
	int		error_check;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	error_check = chdir(tkn->args[0]);
	no_such_file_or_directory(error_check, tkn->args[0]);
	return ;
}

void	cd(t_inst *inst, char *arg)
{
	int		error_check;
	t_tkn *tkn;

	tkn = *(inst->tkn_head);
	update_old_pwd(inst);
	if (arg == NULL)
		cd_home(inst);
	else if (check_arg(inst, arg) == 0 && arg[0] != '~')
		cd_somewhere(inst);
	else if (check_arg(inst, "~") == 0 || check_arg(inst, "~/") == 0)
		cd_tilde_home();
	else if (check_tilde_slash_path(inst) != NULL && ft_strlen(arg) > 1)
	{
		error_check = chdir(check_tilde_slash_path(inst));
		no_such_file_or_directory(error_check, check_tilde_slash_path(inst));
	}
	else if (arg != NULL)
	{
		if (cd_plus_minus(inst) == 0)
		{
			update_pwd(inst);
			return ;
		}
		cd_somewhere(inst);
	}
	update_pwd(inst);
	return ;
}

void	is_a_directory(t_inst *inst)
{
	t_tkn *tkn;

	tkn = *(inst->tkn_head);
	if (check_cmd(inst, tkn->cmd) == 0)
		printf("minishell: %s: is a directory\n", tkn->cmd);
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

int		substitute_tilde(t_inst *inst, int check)
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

int		it_is_a_directory_there(t_inst *inst)
{
	t_tkn *tkn;

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
		return (no_such_file_or_directory_1(0, tkn->cmd));
	return (1);
}

int		your_wish_is_my_command(t_inst *inst, t_tkn *tkn)
{
	char 	*hold_cmd_for_me;
	int 	exit_status;

	exit_status = 0;
	if (tkn->cmd != NULL)
		hold_cmd_for_me = ft_strdup(tkn->cmd);
	while (tkn)
	{
		if (check_cmd(inst, "cd") == 0)
			cd(inst, tkn->args[0]);
		else if (check_pwd(inst) == 0)
			pwd(inst);
		else if (check_env(inst) == 0)
			env(inst);
		else if (check_cmd(inst, "unset") == 0)
			 exit_status = unset(inst, tkn->args);
		else if (tkn->cmd[0] != '~' && tkn->cmd[1] != '/')
			printf("minishell: %s: command not found\n", hold_cmd_for_me);
		else if (it_is_a_directory_there(inst) == 0)
			is_a_directory(inst);
		else if (it_is_a_directory_there(inst) == 1)
			no_such_file_or_directory_1(1, tkn->cmd);
		tkn = tkn->next;
	}
	free(hold_cmd_for_me);
	return (exit_status);
}
