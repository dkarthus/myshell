#include "../../../includes/minishell.h"

void	export_tilde(char *arg)
{
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		g_exit_status = 1;
		error_exit(-5);
	}
	if (arg != NULL)
		free(arg);
	arg = ft_strdup(home_value);
	if (arg == NULL)
		error_exit(-6);
	else
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
	}
}

void	export_tilde_slash(char *arg)
{
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		g_exit_status = 1;
		error_exit(-5);
	}
	if (arg != NULL)
		free(arg);
	arg = ft_strjoin(home_value, "/");
	if (arg == NULL)
		error_exit(-6);
	else
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
	}
}

void	export_tilde_slash_s(char *arg)
{
	char	*home_value;
	char	*hold_str_for_me;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		g_exit_status = 1;
		error_exit(-5);
	}
	hold_str_for_me = ft_substr(arg, 1, ft_strlen(arg) - 1);
	if (hold_str_for_me == NULL)
		error_exit(-6);
	if (arg != NULL)
		free(arg);
	arg = ft_strjoin(home_value, hold_str_for_me);
	if (arg == NULL)
		error_exit(-6);
	else
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
		free(hold_str_for_me);
	}
}

int	export_tilde_minus(t_inst *inst, char *arg)
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
	arg = ft_strdup(old_pwd);
	if (arg == NULL)
		error_exit(-6);
	else
	{
		print_export_not_a_valid_identifier(arg);
		free(arg);
	}
	return (0);
}
