#include "../../../includes/minishell.h"

static int	check_for_tilde_minus(t_inst *inst, char *first_arg)
{
	if (((first_arg != NULL)
			&& ((check_arg(inst, "~-") == 0)
				|| (check_arg(inst, "~-/") == 0))) == 1)
		return (0);
	return (1);
}

static int	check_for_tilde_minus_slash_s(char *first_arg)
{
	if (((first_arg != NULL)
			&& (first_arg[0] == '~')
			&& (first_arg[1] == '-')
			&& (first_arg[2] == '/')
			&& (first_arg[3] != '\0')) == 1)
		return (0);
	return (1);
}

static int	we_just_started_and_no_arguments(char *old_pwd, char *first_arg)
{
	if ((old_pwd == NULL && first_arg == NULL) == 1)
		return (0);
	return (1);
}

int	update_old_pwd(t_inst *inst)
{
	char	*old_pwd;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	old_pwd = NULL;
	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (we_just_started_and_no_arguments(old_pwd, tkn->args[1]) == 0)
	{
		if (update(inst) == 1)
			return (g_exit_status);
	}
	else if (check_for_tilde_minus(inst, tkn->args[1]) == 0)
		return (update_1(inst, old_pwd));
	else
	{
		if (check_for_tilde_minus_slash_s(tkn->args[1]) == 0)
			return (update_1(inst, old_pwd));
		else
			return (update_2(inst, old_pwd));
	}
	return (0);
}
