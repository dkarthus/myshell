#include "../../../includes/minishell.h"

void	print_export_not_a_valid_identifier(char *arg)
{
	printf("minishell: export: `%s': not a valid identifier\n", arg);
	exit_status = 1;
}

void	export_tilde(char *arg)
{
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		exit_status = 1;
		error_exit(-5);
	}
	if (arg != NULL)
		free(arg);
	arg = ft_strdup(home_value);
	print_export_not_a_valid_identifier(arg);
}

void	export_tilde_slash(char *arg)
{
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		exit_status = 1;
		error_exit(-5);
	}
	if (arg != NULL)
		free(arg);
	arg = ft_strjoin(home_value, "/");
	print_export_not_a_valid_identifier(arg);
}

void	export_tilde_slash_s(char *arg)
{
	char	*home_value;
	char	*hold_str_for_me;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		exit_status = 1;
		error_exit(-5);
	}
	hold_str_for_me = ft_substr(arg, 1, ft_strlen(arg) - 1);
	free(arg);
	arg = ft_strjoin(home_value, hold_str_for_me);
	print_export_not_a_valid_identifier(arg);
}

int	export_tilde_minus(t_inst *inst, char *arg)
{
	char	*old_pwd;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_export_not_a_valid_identifier(arg);
		return (exit_status);
	}
	free(arg);
	arg = ft_strdup(old_pwd);
	print_export_not_a_valid_identifier(arg);
	return (0);
}
