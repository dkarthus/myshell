#include "../../includes/minishell.h"

int	if_for_unset(t_inst *inst, t_unset *u, char *arg)
{
	if (env_name(arg) == 0)
		print_not_a_valid_identifier(inst, arg);
	else if (env_name(arg) == u->semicolon)
		return (inst->exit_status);
	else if (env_name(arg) == u->tilde)
		unset_tilde(inst, arg);
	else if (env_name(arg) == u->tilde_slash)
		unset_tilde_slash(inst, arg);
	else if (env_name(arg) == u->tilde_slash_something)
		unset_tilde_slash_s(inst, arg);
	return (1);
}

void	if_for_unset_1(t_inst *inst, t_unset *u, char *arg, char *first_arg)
{
	if (env_name(arg) == u->tilde_minus)
		inst->exit_status = unset_tilde_minus(inst, arg);
	else if (env_name(arg) == u->tilde_minus_slash)
		inst->exit_status = unset_tilde_minus_slash(inst, arg);
	else if (env_name(arg) == u->tilde_minus_slash_something)
		inst->exit_status = unset_tilde_minus_slash_s(inst, arg);
	else if (env_name(arg) == u->tilde_plus)
		inst->exit_status = unset_tilde_plus(inst, arg);
	else if (env_name(arg) == u->tilde_plus_slash)
		inst->exit_status = unset_tilde_plus_slash(inst, arg);
	else if (env_name(arg) == u->tilde_plus_slash_something)
		inst->exit_status = unset_tilde_plus_slash_s(inst, arg);
	else
	{
		u->error_check = ft_unset_env_var(first_arg, inst->env_head);
		if (u->error_check == 0)
			inst->exit_status = 1;
	}
}

void	initialize_variables_for_unset(t_inst *inst, t_unset *u)
{
	u->i = 1;
	inst->exit_status = 0;
	u->semicolon = 2;
	u->tilde = 3;
	u->tilde_slash = 4;
	u->tilde_slash_something = 5;
	u->tilde_minus = 6;
	u->tilde_minus_slash = 7;
	u->tilde_minus_slash_something = 8;
	u->tilde_plus = 9;
	u->tilde_plus_slash = 10;
	u->tilde_plus_slash_something = 11;
}

int	unset(t_inst *inst, char **args)
{
	t_unset	u;

	initialize_variables_for_unset(inst, &u);
	if (args[1] != NULL)
	{
		while (args[u.i] != NULL)
		{
			inst->exit_status = if_for_unset(inst, &u, args[u.i]);
			if (inst->exit_status == 0)
				return (inst->exit_status);
			if_for_unset_1(inst, &u, args[u.i], args[1]);
			u.i++;
		}
	}
	return (inst->exit_status);
}
