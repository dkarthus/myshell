#include "../../../includes/minishell.h"

void	print_export_not_a_valid_identifier(int fd_out_save, char *arg)
{
	ft_putstr_fd("minishell: export: `", fd_out_save);
	ft_putstr_fd(arg, fd_out_save);
	ft_putstr_fd("': not a valid identifier\n", fd_out_save);
	g_exit_status = 1;
}

void	export_semicolon_equal(t_inst *inst, t_u_e *e)
{
	print_export(inst);
	ft_putstr_fd("minishell: =", inst->fd_out_save);
	ft_putstr_fd(e->value, inst->fd_out_save);
	ft_putstr_fd(": command not found\n", inst->fd_out_save);
}

void	export_semicolon(t_inst *inst, char *arg)
{
	char	*str;

	print_export(inst);
	str = ft_substr(arg, 1, ft_strlen(arg) - 1);
	if (str == NULL)
		error_exit(inst->fd_out_save, -6);
	ft_putstr_fd("minishell: ", inst->fd_out_save);
	ft_putstr_fd(arg, inst->fd_out_save);
	ft_putstr_fd(": command not found\n", inst->fd_out_save);
	if (str != NULL)
		free(str);
}

unsigned int	export_arg(t_inst *inst, t_u_e *e, char *arg)
{
	e->error_check = ft_add_env_elem(arg, inst->env_head);
	if (e->error_check == 0)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (0);
}
