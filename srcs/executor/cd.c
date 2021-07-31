#include "../../includes/minishell.h"
#include "../../includes/error_exit.h"

int		update_old_pwd(t_inst *inst)
{
	char	dir[2048];
	char 	*error_check_char_p;
	int 	error_check_int;
	char	*old_pwd;

	error_check_char_p = getcwd(dir, 2048);
	if (error_check_char_p == NULL)
		error_exit(inst, -2);
	old_pwd = ft_strjoin("OLDPWD=", dir);
	error_check_int = ft_add_env_elem(old_pwd, inst->env_head);
	if (error_check_int == 0)
		error_exit(inst, -3);
	free(old_pwd);
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
		error_exit(inst, -2);
	pwd = ft_strjoin("PWD=", dir);
	error_check_int = ft_add_env_elem(pwd, inst->env_head);
	if (error_check_int == 0)
		error_exit(inst, -4);
	free(pwd);
	return (0);
}

void	no_such_file_or_directory(int error_check, const char *str)
{
	int	zero;

	zero = 0;
	if (error_check != zero)
		printf("minishell: cd: %s: No such file or directory\n", str);
	return ;
}

void	cd_tilde_home(t_inst *inst)
{
	int		error_check_int;
	char	*home_value;

	error_check_int = 0;
	home_value = getenv("HOME");
	if (home_value == NULL)
		error_exit(inst, -5);
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

//int		is_slash(t_inst *inst)
//{
//	size_t 	i;
//	size_t 	count;
//	t_tkn	*tkn;
//	size_t	len;
//	char	c;
//
//	i = 0;
//	count = 0;
//	c = 92;
//	tkn = *(inst->tkn_head);
//	len = ft_strlen(tkn->args[0]);
//	printf ("len = %zu\n", len);
//	while (tkn->args[0][i] != '\0')
//	{
//		while (tkn->args[0][i] == c)
//			count++;
//		i++;
//	}
//	printf ("i = %zu\n", i);
//	printf ("count = %zu\n", i);
//	if (len == count)
//		return (0);
//	else
//		return (1);
//}

//void	cd_slash(t_inst *inst)
//{
//	int		error_check_int;
//	t_tkn	*tkn;
//
//	error_check_int = 0;
//	tkn = *(inst->tkn_head);
//	if (is_slash(inst) == 0)
//	{
//		error_check_int = chdir(tkn->args[0]);
//		no_such_file_or_directory(error_check_int, tkn->args[0]);
//	}
//}

char	*check_tilde_slash_path(t_inst *inst)
{
	t_tkn	*tkn;
	int 	error_check_int;
	char	*absolute_path;
	char	*home_value;

	tkn = *(inst->tkn_head);
	absolute_path = NULL;
	home_value = getenv("HOME");
	if (home_value == NULL)
		error_exit(inst,-5);
	else
	{
		absolute_path = ft_strjoin(home_value, &tkn->args[0][1]);
		error_check_int = chdir(absolute_path);
		if (error_check_int != 0)
			return (NULL);
	}
	return (absolute_path);
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
	char	*absolute_path;
	char	*pwd;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	absolute_path = NULL;
	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
		no_such_file_or_directory(error_check_int, tkn->args[0]);
	else
	{
		absolute_path = ft_strjoin(pwd, &tkn->args[0][1]);
		error_check_int = chdir(absolute_path);
		if (error_check_int != 0)
			return (NULL);
	}
	return (absolute_path);
}

char	*check_tilde_minus_path(t_inst *inst)
{
	t_tkn	*tkn;
	int 	error_check_int;
	char	*absolute_path;
	char	*old_pwd;

	error_check_int = 0;
	tkn = *(inst->tkn_head);
	absolute_path = NULL;
	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
		no_such_file_or_directory(error_check_int, tkn->args[0]);
	else
	{
		absolute_path = ft_strjoin(old_pwd, &tkn->args[0][1]);
		error_check_int = chdir(absolute_path);
		if (error_check_int != 0)
			return (NULL);
	}
	return (absolute_path);
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

void	cd(t_inst *inst)
{
	int		error_check;
	t_tkn *tkn;

	tkn = *(inst->tkn_head);
	update_old_pwd(inst);
	if (tkn->args[0] == NULL)
		cd_home(inst);
	else if (check_arg(inst, "/") == 0)
//		cd_slash(inst);
		chdir(tkn->args[0]);
	else if (check_arg(inst, "~") == 0 || check_arg(inst, "~/") == 0)
		cd_tilde_home(inst);
	else if (check_tilde_slash_path(inst) != NULL && ft_strlen(tkn->args[0]) > 1)
	{
		error_check = chdir(check_tilde_slash_path(inst));
		no_such_file_or_directory(error_check, check_tilde_slash_path(inst));
	}
	else if (tkn->args[0] != NULL)
	{
		if (cd_plus_minus(inst) == 0)
		{
			update_pwd(inst);
			return ;
		}
		error_check = chdir(tkn->args[0]);
		no_such_file_or_directory(error_check, tkn->args[0]);
	}
	update_pwd(inst);
	return ;
}
/*

int		command(t_inst *inst, const char *str)
{
	t_tkn *tkn;
	size_t	len;

	tkn = *(inst->tkn_head);
	inst = NULL;
	len = ft_strlen(str);
	if (ft_strlen(tkn->cmd) == len
		&& ft_strncmp(tkn->cmd, str, len) == 0)
		return (0);
	else
		return (1);
}
*/

int		your_wish_is_my_command(t_inst *inst)
{
	t_tkn *tmp;

	tmp = *(inst->tkn_head);
	while (tmp)
	{
		if (ft_strncmp(tmp->cmd, "cd", ft_strlen(tmp->cmd)) == 0)
			cd(inst);

		tmp = tmp->next;
	}
		return (0);
}
