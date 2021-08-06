#include "../../../includes/minishell.h"

int	unset_tilde_minus_slash(t_inst *inst, char *arg)
{
	char	*old_pwd;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_unset_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	free(arg);
	arg = ft_strjoin(old_pwd, "/");
	print_unset_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_minus_slash_s(t_inst *inst, char *arg)
{
	char	*old_pwd;
	char	*hold_str_for_me;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_unset_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	hold_str_for_me = ft_substr(arg, 2, ft_strlen(arg) - 1);
	free(arg);
	arg = ft_strjoin(old_pwd, hold_str_for_me);
	print_unset_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_plus(t_inst *inst, char *arg)
{
	char	*pwd;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_unset_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	free(arg);
	arg = ft_strdup(pwd);
	print_unset_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_plus_slash(t_inst *inst, char *arg)
{
	char	*pwd;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_unset_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	free(arg);
	arg = ft_strjoin(pwd, "/");
	print_unset_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_plus_slash_s(t_inst *inst, char *arg)
{
	char	*pwd;
	char	*hold_str_for_me;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_unset_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	hold_str_for_me = ft_substr(arg, 2, ft_strlen(arg) - 1);
	free(arg);
	arg = ft_strjoin(pwd, hold_str_for_me);
	print_unset_not_a_valid_identifier(inst, arg);
	return (0);
}
