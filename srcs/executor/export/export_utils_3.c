#include "../../../includes/minishell.h"

void	print_export_not_a_valid_identifier(char *arg)
{
	printf("\033[90mminishell: export: `%s': "
		   "not a valid identifier\033[0m\n", arg);
	g_exit_status = 1;
}

void	export_semicolon_equal(t_inst *inst, t_u_e *e)
{
	print_export(inst);
	printf("\033[90mminishell: =%s: command not found\033[0m\n", e->value);
}

void	export_semicolon(t_inst *inst, char *arg)
{
	char	*str;

	print_export(inst);
	str = ft_substr(arg, 1, ft_strlen(arg) - 1);
	if (str == NULL)
		error_exit(-6);
	printf("\033[90mminishell: %s: command not found\033[0m\n", str);
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
