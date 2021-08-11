#include "../../../includes/minishell.h"

int	export_tilde_minus_slash(t_inst *inst, char *arg)
{
	char	*old_pwd;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_export_not_a_valid_identifier(arg);
		return (g_exit_status);
	}
	if (arg != NULL)
		free(arg);
	arg = ft_strjoin(old_pwd, "/");
	if (arg == NULL)
		error_exit(-6);
	else
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
	}
	return (g_exit_status);
}

int	export_tilde_minus_slash_s(t_inst *inst, char *arg)
{
	char	*old_pwd;
	char	*hold_str_for_me;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_export_not_a_valid_identifier(arg);
		return (g_exit_status);
	}
	hold_str_for_me = ft_substr(arg, 2, ft_strlen(arg) - 1);
	if (hold_str_for_me == NULL)
		error_exit(-6);
	if (arg != NULL)
		free(arg);
	arg = ft_strjoin(old_pwd, hold_str_for_me);
	if (arg == NULL)
		error_exit(-6);
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
		free(hold_str_for_me);
	}
	return (g_exit_status);
}

int	export_tilde_plus(t_inst *inst, char *arg)
{
	char	*pwd;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_export_not_a_valid_identifier(arg);
		return (g_exit_status);
	}
	if (arg != NULL)
		free(arg);
	arg = ft_strdup(pwd);
	if (arg == NULL)
		error_exit(-6);
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
	}
	return (g_exit_status);
}

int	export_tilde_plus_slash(t_inst *inst, char *arg)
{
	char	*pwd;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_export_not_a_valid_identifier(arg);
		return (g_exit_status);
	}
	if (arg != NULL)
		free(arg);
	arg = ft_strjoin(pwd, "/");
	if (arg == NULL)
		error_exit(-6);
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
	}
	return (g_exit_status);
}

int	export_tilde_plus_slash_s(t_inst *inst, char *arg)
{
	char	*pwd;
	char	*hold_str_for_me;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_export_not_a_valid_identifier(arg);
		return (g_exit_status);
	}
	hold_str_for_me = ft_substr(arg, 2, ft_strlen(arg) - 1);
	if (hold_str_for_me == NULL)
		error_exit(-6);
	if (arg != NULL)
		free(arg);
	arg = ft_strjoin(pwd, hold_str_for_me);
	if (arg == NULL)
		error_exit(-6);
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
		free(hold_str_for_me);
	}
	return (g_exit_status);
}
