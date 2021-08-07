#include "../../../includes/minishell.h"


char		**ft_sorting_exp(char **str)
{
	char	*sort;
	int		i;
	int		m;

	if (str == NULL)
		return (NULL);
	i = 0;
	m = 1;
	while (str[i] != NULL)
	{
		m = 1;
		while (str[i + m] != NULL)
		{
			if (ft_strcmp(str[i], str[i + m]) > 0)
			{
				sort = str[i + m];
				str[i + m] = str[i];
				str[i] = sort;
			}
			m++;
		}
		i++;
	}
	return (str);
}

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
				printf("declare -x %s=\"\"\n", env->key);
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
			printf("declare -x %s=\"\"\n", env->key);
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

void	initialize_variables_for_export(t_u_e *e)
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

void	free_key_and_value(t_u_e *e)
{
	if (e->key != NULL)
		free(e->key);
	if (e->value != NULL)
		free(e->value);
}

void	split_the_line_for_key_and_value(t_u_e *e, char *arg)
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
			error_exit(-6);
		e->value = ft_substr(arg, i + 1, ft_strlen(arg));
		if (e->value == NULL)
			error_exit(-6);
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
		exit_status = 1;
		return (exit_status);
	}
	return (0);
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
				exit_status =	export_tilde_minus_slash_s(inst, args[e.i]);
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
	}
	return (0);
}