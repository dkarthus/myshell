#include "../../../includes/minishell.h"

static void	initialize_variables_for_export(t_u_e *e)
{
	e->i = 1;
	e->error_check = 0;
	exit_status = 0;
	e->arg = 0;
	e->failure = 1;
	e->underscore = 2;
	e->semicolon_underscore = 2;
	e->tilde = 3;
	e->tilde_slash = 4;
	e->tilde_slash_s = 5;
	e->tilde_minus = 6;
	e->tilde_minus_slash = 7;
	e->tilde_minus_slash_s = 8;
	e->tilde_plus = 9;
	e->tilde_plus_slash = 10;
	e->tilde_plus_slash_s = 11;
	e->comment_symbol = 12;
	e->semicolon = 13;
	e->semicolon_s = 14;
	e->equal_sign = 15;
	e->key = NULL;
	e->value = NULL;
}

int	export(t_inst *inst, char **args)
{
	t_u_e	e;

	initialize_variables_for_export(&e);
	if (args[1] == NULL)
	{
		print_export(inst);
		return (exit_status);
	}
	else if (args[1] != NULL)
	{
		while (args[e.i] != NULL)
		{
			if (ft_strchr(args[e.i], '=') != NULL)
			{
				split_the_line_for_key_and_value(&e, args[e.i]);
				if (key(&e, args[e.i]) == e.semicolon)
					print_export(inst);
				else if (key(&e, args[e.i]) == e.semicolon_s)
					export_semicolon_equal(inst, &e);
				else if (key(&e, args[e.i]) == e.equal_sign)
					print_export_not_a_valid_identifier(args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde)
					export_tilde(args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_slash)
					export_tilde_slash(args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_slash_s)
					export_tilde_slash_s(args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_minus)
					exit_status = export_tilde_minus(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_minus_slash)
					exit_status = export_tilde_minus_slash(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_minus_slash_s)
					exit_status = export_tilde_minus_slash_s(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_plus)
					exit_status = export_tilde_plus(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_plus_slash)
					exit_status = export_tilde_plus_slash(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_plus_slash_s)
					exit_status = export_tilde_plus_slash_s(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.comment_symbol)
					exit_status = export_comment_symbol(inst);
				else if (key(&e, args[e.i]) == e.arg)
					exit_status = export_arg(inst, &e, args[e.i]);
				else if (key(&e, args[e.i]) == e.failure)
					print_export_not_a_valid_identifier(args[e.i]);
			}
			else
			{
				if (key(&e, args[e.i]) == e.semicolon)
					print_export(inst);
				else if (key(&e, args[e.i]) == e.semicolon_s)
					export_semicolon(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.underscore)
					return (0);
				else if (key(&e, args[e.i]) == e.tilde)
					export_tilde(args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_slash)
					export_tilde_slash(args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_slash_s)
					export_tilde_slash_s(args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_minus)
					exit_status = export_tilde_minus(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_minus_slash)
					exit_status = export_tilde_minus_slash(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_minus_slash_s)
					exit_status = export_tilde_minus_slash_s(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_plus)
					exit_status = export_tilde_plus(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_plus_slash)
					exit_status = export_tilde_plus_slash(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.tilde_plus_slash_s)
					exit_status = export_tilde_plus_slash_s(inst, args[e.i]);
				else if (key(&e, args[e.i]) == e.comment_symbol)
					exit_status = export_comment_symbol(inst);
				else if (key(&e, args[e.i]) == e.arg)
					exit_status = export_arg(inst, &e, args[e.i]);
				else if (key(&e, args[e.i]) == e.failure)
					print_export_not_a_valid_identifier(args[e.i]);
			}
			e.i++;
		}
	}
	return (0);
}
