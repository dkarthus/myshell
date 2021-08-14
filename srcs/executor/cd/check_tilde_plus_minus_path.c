#include "../../../includes/minishell.h"

int	check_arg(t_inst *inst, const char *str)
{
	t_tkn	*tkn;
	size_t	len;

	tkn = *(inst->tkn_head);
	len = ft_strlen(str);
	if (ft_strlen(tkn->args[1]) == len
		&& ft_strncmp(tkn->args[1], str, len) == 0)
		return (0);
	else
		return (1);
}

static void	check_for_tilde_minus_path(t_tkn *tkn, char *old_pwd)
{
	char	*hold_str_for_me;

	if (tkn->args[1][0] == '~'
		&& tkn->args[1][1] == '-'
		&& tkn->args[1][2] == '/'
		&& tkn->args[1][3] != '\0')
	{
		hold_str_for_me = ft_strjoin(old_pwd, &tkn->args[1][2]);
		free(tkn->args[1]);
		tkn->args[1] = ft_strdup(hold_str_for_me);
		free(hold_str_for_me);
	}
}

char	*check_tilde_minus_path(t_inst *inst)
{
	t_tkn	*tkn;
	int		error_check_int;
	char	*old_pwd;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
		no_such_file_or_directory(inst->fd_out_save,
			  error_check_int, tkn->args[1]);
	else
	{
		check_for_tilde_minus_path(tkn, old_pwd);
		error_check_int = chdir(tkn->args[1]);
		if (error_check_int != 0)
			return (NULL);
	}
	return (tkn->args[1]);
}

static void	check_for_tilde_plus_path(t_tkn *tkn, int fd_out_save, char *pwd)
{
	char	*hold_str_for_me;

	if (tkn->args[1][0] == '~'
		&& tkn->args[1][1] == '+'
		&& tkn->args[1][2] == '/')
	{
		hold_str_for_me = ft_strjoin(pwd, &tkn->args[1][2]);
		if (hold_str_for_me == NULL)
			(error_exit(fd_out_save, -6));
		free(tkn->args[1]);
		tkn->args[1] = ft_strdup(hold_str_for_me);
		if (tkn->args[1] == NULL)
			(error_exit(fd_out_save, -6));
		free(hold_str_for_me);
	}
}

char	*check_tilde_plus_path(t_inst *inst)
{
	t_tkn	*tkn;
	int		error_check_int;
	char	*pwd;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
		no_such_file_or_directory(inst->fd_out_save,
			  error_check_int, tkn->args[1]);
	else
	{
		check_for_tilde_plus_path(tkn, inst->fd_out_save, pwd);
		error_check_int = chdir(tkn->args[1]);
		if (error_check_int != 0)
			return (NULL);
	}
	return (tkn->args[1]);
}
