#include "../../../includes/minishell.h"

void	if_for_export(t_inst *inst, t_u_e *e, char *arg)
{
	if (key(e, arg) == e->semicolon)
		print_export(inst);
	else if (key(e, arg) == e->semicolon_s)
		export_semicolon_equal(inst, e);
	else if (key(e, arg) == e->equal_sign)
		print_export_not_a_valid_identifier(arg);
	else if (key(e, arg) == e->tilde)
		export_tilde(arg);
	else if (key(e, arg) == e->tilde_slash)
		export_tilde_slash(arg);
	else if (key(e, arg) == e->tilde_slash_s)
		export_tilde_slash_s(arg);
	else if (key(e, arg) == e->tilde_minus)
		exit_status = export_tilde_minus(inst, arg);
	else if (key(e, arg) == e->tilde_minus_slash)
		exit_status = export_tilde_minus_slash(inst, arg);
	else if (key(e, arg) == e->tilde_minus_slash_s)
		exit_status = export_tilde_minus_slash_s(inst, arg);
	else if (key(e, arg) == e->tilde_plus)
		exit_status = export_tilde_plus(inst, arg);
	else if (key(e, arg) == e->tilde_plus_slash)
		exit_status = export_tilde_plus_slash(inst, arg);
	else if (key(e, arg) == e->tilde_plus_slash_s)
		exit_status = export_tilde_plus_slash_s(inst, arg);
}

void	if_for_export_1(t_inst *inst, t_u_e *e, char *arg)
{
	if (key(e, arg) == e->comment_symbol)
		exit_status = export_comment_symbol(inst);
	else if (key(e, arg) == e->arg)
		exit_status = export_arg(inst, e, arg);
	else if (key(e, arg) == e->failure)
		print_export_not_a_valid_identifier(arg);
}

unsigned int	if_for_export_2(t_inst *inst, t_u_e *e, char *arg)
{
	if (key(e, arg) == e->semicolon)
		print_export(inst);
	else if (key(e, arg) == e->semicolon_s)
		export_semicolon(inst, arg);
	else if (key(e, arg) == e->underscore)
		return (0);
	else if (key(e, arg) == e->tilde)
		export_tilde(arg);
	else if (key(e, arg) == e->tilde_slash)
		export_tilde_slash(arg);
	else if (key(e, arg) == e->tilde_slash_s)
		export_tilde_slash_s(arg);
	else if (key(e, arg) == e->tilde_minus)
		exit_status = export_tilde_minus(inst, arg);
	else if (key(e, arg) == e->tilde_minus_slash)
		exit_status = export_tilde_minus_slash(inst, arg);
	return (1);
}

void	if_for_export_3(t_inst *inst, t_u_e *e, char *arg)
{
	if (key(e, arg) == e->tilde_minus_slash_s)
		exit_status = export_tilde_minus_slash_s(inst, arg);
	else if (key(e, arg) == e->tilde_plus)
		exit_status = export_tilde_plus(inst, arg);
	else if (key(e, arg) == e->tilde_plus_slash)
		exit_status = export_tilde_plus_slash(inst, arg);
	else if (key(e, arg) == e->tilde_plus_slash_s)
		exit_status = export_tilde_plus_slash_s(inst, arg);
	else if (key(e, arg) == e->comment_symbol)
		exit_status = export_comment_symbol(inst);
	else if (key(e, arg) == e->arg)
		exit_status = export_arg(inst, e, arg);
	else if (key(e, arg) == e->failure)
		print_export_not_a_valid_identifier(arg);
}
