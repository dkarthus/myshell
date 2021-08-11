#include "../../../includes/minishell.h"

void	if_for_export(t_inst *inst, t_u_e *e, char *arg)
{
	if (key(e, arg) == e->semicolon)
		print_export(inst);
	else if (key(e, arg) == e->semicolon_s)
		export_semicolon_equal(inst, e);
	else if (key(e, arg) == e->equal_sign)
		print_export_not_a_valid_identifier(arg);
	else if (key(e, arg) == e->comment_symbol)
		g_exit_status = export_comment_symbol(inst);
	else if (key(e, arg) == e->arg)
		g_exit_status = export_arg(inst, e, arg);
	else if (key(e, arg) == e->failure)
		print_export_not_a_valid_identifier(arg);
}

unsigned int	if_for_export_1(t_inst *inst, t_u_e *e, char *arg)
{
	if (key(e, arg) == e->semicolon)
		print_export(inst);
	else if (key(e, arg) == e->semicolon_s)
		export_semicolon(inst, arg);
	else if (key(e, arg) == e->underscore)
		return (0);
	return (1);
}

void	if_for_export_2(t_inst *inst, t_u_e *e, char *arg)
{
	if (key(e, arg) == e->comment_symbol)
		g_exit_status = export_comment_symbol(inst);
	else if (key(e, arg) == e->arg)
		g_exit_status = export_arg(inst, e, arg);
	else if (key(e, arg) == e->failure)
		print_export_not_a_valid_identifier(arg);
}
