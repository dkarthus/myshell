#include "../../../includes/minishell.h"

//int	if_for_export(t_inst *inst, t_u_e *e, char *arg)
//{
//	if (export_env_name(arg) == 0)
//		print_export_not_a_valid_identifier(inst, arg);
//	else if (export_env_name(arg) == e->semicolon_underscore)
//		return (inst->exit_status);
//	else if (export_env_name(arg) == e->tilde)
//		export_tilde(inst, arg);
//	else if (export_env_name(arg) == e->tilde_slash)
//		export_tilde_slash(inst, arg);
//	else if (export_env_name(arg) == e->tilde_slash_something)
//		export_tilde_slash_s(inst, arg);
//	return (1);
//}
//
//void	if_for_export_1(t_inst *inst, t_u_e *e, char *arg, char *next_arg)
//{
//	if (export_env_name(arg) == e->tilde_minus)
//		inst->exit_status = export_tilde_minus(inst, arg);
//	else if (export_env_name(arg) == e->tilde_minus_slash)
//		inst->exit_status = export_tilde_minus_slash(inst, arg);
//	else if (export_env_name(arg) == e->tilde_minus_slash_something)
//		inst->exit_status =	export_tilde_minus_slash_s(inst, arg);
//	else if (export_env_name(arg) == e->tilde_plus)
//		inst->exit_status = export_tilde_plus(inst, arg);
//	else if (export_env_name(arg) == e->tilde_plus_slash)
//		inst->exit_status = export_tilde_plus_slash(inst, arg);
//	else if (export_env_name(arg) == e->tilde_plus_slash_something)
//		inst->exit_status = export_tilde_plus_slash_s(inst, arg);
//	else if (export_env_name(arg) == e->comment_symbol)
//		inst->exit_status = export_comment_symbol(inst->env_head);
//	else
//	{
//		e->error_check = export_var(inst, e, next_arg);
//		if (e->error_check == 0)
//			inst->exit_status = 1;
//	}
//}

void	print_export(t_inst *inst)
{
	t_env	*env;

	env = *(inst->env_head);
	while (env->next != NULL)
	{
		if (env->value[0] == '\0')
		{
			printf("declare -x %s\n", env->key);
			env = env->next;
			continue;
		}
		else
		{
			printf("declare -x %s", env->key);
			printf("=\"%s\"\n", env->value);
		}
		env = env->next;
	}
}

void	initialize_variables_for_export(t_inst *inst, t_u_e *e)
{
	e->i = 0;
	e->error_check = 0;
	inst->exit_status = 0;
	e->semicolon_underscore = 2;
	e->tilde = 3;
	e->tilde_slash = 4;
	e->tilde_slash_something = 5;
	e->tilde_minus = 6;
	e->tilde_minus_slash = 7;
	e->tilde_minus_slash_something = 8;
	e->tilde_plus = 9;
	e->tilde_plus_slash = 10;
	e->tilde_plus_slash_something = 11;
	e->comment_symbol = 12;
}

int	export(t_inst *inst, char **args)
{
	t_u_e	e;

	initialize_variables_for_export(inst, &e);
	if (args[0] == NULL)
	{
		print_export(inst);
		return (inst->exit_status);
	}
	else if (args[0] != NULL)
	{
		while (args[e.i] != NULL)
		{
			if (export_env_var(args[e.i]) == 0)
				print_export_not_a_valid_identifier(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.semicolon_underscore)
				return (inst->exit_status);
			else if (export_env_var(args[e.i]) == e.tilde)
				export_tilde(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.tilde_slash)
				export_tilde_slash(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.tilde_slash_something)
				export_tilde_slash_s(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.tilde_minus)
				inst->exit_status = export_tilde_minus(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.tilde_minus_slash)
				inst->exit_status = export_tilde_minus_slash(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.tilde_minus_slash_something)
				inst->exit_status =	export_tilde_minus_slash_s(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.tilde_plus)
				inst->exit_status = export_tilde_plus(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.tilde_plus_slash)
				inst->exit_status = export_tilde_plus_slash(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.tilde_plus_slash_something)
				inst->exit_status = export_tilde_plus_slash_s(inst, args[e.i]);
			else if (export_env_var(args[e.i]) == e.comment_symbol)
				inst->exit_status = export_comment_symbol(inst);
			else
			{
				e.error_check = ft_add_env_elem(args[e.i], inst->env_head);
				if (e.error_check == 0)
				{
					inst->exit_status = 1;
					return (inst->exit_status);
				}
			}
			e.i++;
		}
	}
	return (0);
}