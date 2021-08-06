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
		if (ft_strchr(env->line, '=') != NULL)
		{
			if (env->value[0] == '\0')
			{
				printf("declare -x %s=""\n", env->key);
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
		else
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
	if (ft_strchr(env->line, '=') != NULL)
	{
		if (env->value[0] == '\0')
			printf("declare -x %s=""\n", env->key);
		else
		{
			printf("declare -x %s", env->key);
			printf("=\"%s\"\n", env->value);
		}
	}
	else
	{
		if (env->value[0] == '\0')
			printf("declare -x %s\n", env->key);
		else
		{
			printf("declare -x %s", env->key);
			printf("=\"%s\"\n", env->value);
		}
	}
}

void	initialize_variables_for_export(t_inst *inst, t_u_e *e)
{
	e->i = 1;
	e->failure = 1;
	e->error_check = 0;
	inst->exit_status = 0;
	e->semicolon = 13;
	e->arg = 0;
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
	e->semicolon_s = 14;
	e->equal_sign = 15;
	e->tilde_1 = 16;
	e->tilde_slash_1 = 17;
	e->tilde_slash_s_1 = 18;
	e->tilde_minus_1 = 19;
	e->tilde_minus_slash_1 = 20;
	e->tilde_minus_slash_s_1 = 21;
	e->tilde_plus_1 = 22;
	e->tilde_plus_slash_1 = 23;
	e->tilde_plus_slash_s_1 = 24;
	e->key = NULL;
	e->value = NULL;
}

void	free_key_and_value(t_u_e *e)
{
	if (e->key != NULL)
		free(e->key);
	if (e->value != NULL)
		free(e->value);
}

void	split_the_line_for_key_and_value(t_inst *inst, t_u_e *e, char *arg)
{
	int		i;

	free_key_and_value(e);
	if (ft_strchr(arg, '=') != NULL)
	{
		i = 0;
		while (arg[i] != '=')
			i++;
		e->key = ft_substr(arg, 0, i);
		if (e->key == NULL)
			error_exit(inst, -6);
		e->value = ft_substr(arg, i + 1, ft_strlen(arg));
		if (e->value == NULL)
			error_exit(inst, -6);
//		printf("export %s=\"%s\"\n", e->key, e->value);
	}
}

void	export_semicolon_equal(t_inst *inst, t_u_e *e)
{
	print_export(inst);
	printf("minishell: =%s: command not found\n", e->value);
}

void	export_semicolon(t_inst *inst, char *arg)
{
	char *str;

	print_export(inst);
	str = ft_substr(arg, 1, ft_strlen(arg) - 1);
	printf("minishell: %s: command not found\n", str);
	if (str != NULL)
		free(str);
}

unsigned int	export_arg(t_inst *inst, t_u_e *e, char *arg)
{
	e->error_check = ft_add_env_elem(arg, inst->env_head);
	if (e->error_check == 0)
	{
		inst->exit_status = 1;
		return (inst->exit_status);
	}
	return (0);
}

int	export(t_inst *inst, char **args)
{
	t_u_e	e;

	initialize_variables_for_export(inst, &e);
	if (args[1] == NULL)
	{
		print_export(inst);
		return (inst->exit_status);
	}
	else if (args[1] != NULL)
	{
		if (ft_strchr(args[e.i], '=') != NULL)
		{
			split_the_line_for_key_and_value(inst, &e, args[e.i]);
			if (key(&e, args[e.i]) == e.semicolon_s)
				export_semicolon_equal(inst, &e);
			else if (key(&e, args[e.i]) == e.equal_sign)
				print_export_not_a_valid_identifier(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde)
				export_tilde(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_slash)
				export_tilde_slash(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_slash_s)
				export_tilde_slash_s(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_minus)
				inst->exit_status = export_tilde_minus(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_minus_slash)
				inst->exit_status = export_tilde_minus_slash(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_minus_slash_s)
				inst->exit_status =	export_tilde_minus_slash_s(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_plus)
				inst->exit_status = export_tilde_plus(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_plus_slash)
				inst->exit_status = export_tilde_plus_slash(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_plus_slash_s)
				inst->exit_status = export_tilde_plus_slash_s(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.arg)
				inst->exit_status = export_arg(inst, &e, args[e.i]);
			else if (key(&e, args[e.i]) == e.failure)
				print_export_not_a_valid_identifier(inst, args[e.i]);
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
				export_tilde(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_slash)
				export_tilde_slash(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_slash_s)
				export_tilde_slash_s(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_minus)
				inst->exit_status = export_tilde_minus(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_minus_slash)
				inst->exit_status = export_tilde_minus_slash(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_minus_slash_s)
				inst->exit_status =	export_tilde_minus_slash_s(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_plus)
				inst->exit_status = export_tilde_plus(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_plus_slash)
				inst->exit_status = export_tilde_plus_slash(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.tilde_plus_slash_s)
				inst->exit_status = export_tilde_plus_slash_s(inst, args[e.i]);
			else if (key(&e, args[e.i]) == e.comment_symbol)
				inst->exit_status = export_comment_symbol(inst);
			else if (key(&e, args[e.i]) == e.arg)
				inst->exit_status = export_arg(inst, &e, args[e.i]);
			else if (key(&e, args[e.i]) == e.failure)
				print_export_not_a_valid_identifier(inst, args[e.i]);
		}
	}
	return (0);
}