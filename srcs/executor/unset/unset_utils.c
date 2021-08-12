#include "../../../includes/minishell.h"

void	print_unset_not_a_valid_identifier(char *arg)
{
	printf("minishell: unset: `%s': not a valid identifier\n", arg);
	g_exit_status = 1;
}

void	unset_tilde(char *arg)
{
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		g_exit_status = 1;
		error_exit(-5);
	}
	free(arg);
	arg = ft_strdup(home_value);
	print_unset_not_a_valid_identifier(arg);
}

void	unset_tilde_slash(char *arg)
{
	char	*home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		g_exit_status = 1;
		error_exit(-5);
	}
	free(arg);
	arg = ft_strjoin(home_value, "/");
	print_unset_not_a_valid_identifier(arg);
}

void	unset_tilde_slash_s(char *arg)
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
	free(arg);
	arg = ft_strjoin(home_value, hold_str_for_me);
	print_unset_not_a_valid_identifier(arg);
}

int	unset_tilde_minus(t_inst *inst, char *arg)
{
	char	*old_pwd;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_unset_not_a_valid_identifier(arg);
		return (g_exit_status);
	}
	free(arg);
	arg = ft_strdup(old_pwd);
	print_unset_not_a_valid_identifier(arg);
	return (0);
}
