#include "../../../includes/minishell.h"

static void	initialize_variables_for_export(t_u_e *e)
{
	e->i = 1;
	e->error_check = 0;
	g_exit_status = 0;
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

void	line_contains_equal_sign(t_inst *inst, t_u_e *e, char *arg)
{
	split_the_line_for_key_and_value(e, arg);
	if_for_export(inst, e, arg);
	if_for_export_1(inst, e, arg);
}

int	export(t_inst *inst, char **args)
{
	t_u_e	e;

	initialize_variables_for_export(&e);
	if (args[1] == NULL)
	{
		print_export(inst);
		return (g_exit_status);
	}
	else if (args[1] != NULL)
	{
		while (args[e.i] != NULL)
		{
			if (ft_strchr(args[e.i], '=') != NULL)
				line_contains_equal_sign(inst, &e, args[e.i]);
			else
			{
				if (if_for_export_2(inst, &e, args[e.i]) == 0)
					return (0);
				if_for_export_3(inst, &e, args[e.i]);
			}
			e.i++;
		}
	}
	return (g_exit_status);
}
