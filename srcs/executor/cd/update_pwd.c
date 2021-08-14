#include "../../../includes/minishell.h"

int	cd_somewhere(t_inst *inst)
{
	int		error_check;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	error_check = chdir(tkn->args[1]);
	no_such_file_or_directory(inst->fd_out_save, error_check, tkn->args[1]);
	return (0);
}

int	update_pwd(t_inst *inst)
{
	char	dir[2048];
	char	*error_check_char_p;
	int		error_check_int;
	char	*pwd;

	error_check_char_p = getcwd(dir, 2048);
	if (error_check_char_p == NULL)
		(error_exit(inst->fd_out_save, -2));
	pwd = ft_strjoin("PWD=", dir);
	if (pwd == NULL)
		(error_exit(inst->fd_out_save, -6));
	error_check_int = ft_add_env_elem(pwd, inst->env_head);
	if (error_check_int == 0)
		(error_exit(inst->fd_out_save, -4));
	free(pwd);
	return (0);
}
