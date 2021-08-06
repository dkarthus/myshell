#include "../../../includes/minishell.h"

void	print_unset_not_a_valid_identifier(t_inst *inst, char *arg)
{
	printf("minishell: unset: `%s': not a valid identifier\n", arg);
	inst->exit_status = 1;
}

void	unset_tilde(t_inst *inst, char *arg)
{
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		inst->exit_status = 1;
		error_exit(inst, -5);
	}
	free(arg);
	arg = ft_strdup(home_value);
	print_unset_not_a_valid_identifier(inst, arg);
}

void	unset_tilde_slash(t_inst *inst, char *arg)
{
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		inst->exit_status = 1;
		error_exit(inst, -5);
	}
	free(arg);
	arg = ft_strjoin(home_value, "/");
	print_unset_not_a_valid_identifier(inst, arg);
}

void	unset_tilde_slash_s(t_inst *inst, char *arg)
{
	char	*home_value;
	char	*hold_str_for_me;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		inst->exit_status = 1;
		error_exit(inst, -5);
	}
	hold_str_for_me = ft_substr(arg, 1, ft_strlen(arg) - 1);
	free(arg);
	arg = ft_strjoin(home_value, hold_str_for_me);
	print_unset_not_a_valid_identifier(inst, arg);
}

int	unset_tilde_minus(t_inst *inst, char *arg)
{
	char	*old_pwd;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_unset_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	free(arg);
	arg = ft_strdup(old_pwd);
	print_unset_not_a_valid_identifier(inst, arg);
	return (0);
}
