#include "../../../includes/minishell.h"

int	update_2(t_inst *inst, char *old_pwd)
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

int	update_1(t_inst *inst, char *old_pwd)
{
	char	*error_check_p;
	int		error_check_int;

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

int	update(t_inst *inst)
{
	int		error_check_int;
	char	*error_check_p;
	char	*old_pwd;

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
