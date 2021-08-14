#include "../../../includes/minishell.h"

static void	initialize_variables_for_export(t_u_e *e)
{
	e->i = 1;
	e->error_check = 0;
	g_exit_status = 0;
	e->arg = 0;
	e->arg_plus = 0;
	e->failure = 1;
	e->underscore = 2;
	e->semicolon_underscore = 2;
	e->comment_symbol = 3;
	e->semicolon = 4;
	e->semicolon_s = 5;
	e->equal_sign = 6;
	e->key = NULL;
	e->value = NULL;
}

void	line_contains_equal_sign(t_inst *inst, t_u_e *e, char *arg)
{
	split_the_line_for_key_and_value(e, inst->fd_out_save, arg);
	if_for_export(inst, e, arg);
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
				if (if_for_export_1(inst, &e, args[e.i]) == 0)
					return (0);
				if_for_export_2(inst, &e, args[e.i]);
			}
			e.i++;
		}
	}
	free_key_and_value(&e);
	return (g_exit_status);
}
