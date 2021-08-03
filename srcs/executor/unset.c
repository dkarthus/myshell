#include "../../includes/minishell.h"

void	print_not_a_valid_identifier(t_inst *inst, char *arg)
{
	printf("minishell: unset: `%s': not a valid identifier\n", arg);
	inst->exit_status = 1;
}

void	unset_tilde(t_inst *inst, char *arg)
{
	char *home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		inst->exit_status = 1;
		error_exit(-5);
	}
	free(arg);
	arg = ft_strdup(home_value);
	print_not_a_valid_identifier(inst, arg);
}

void	unset_tilde_slash(t_inst *inst, char *arg)
{
	char *home_value;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		inst->exit_status = 1;
		error_exit(-5);
	}
	free(arg);
	arg = ft_strjoin(home_value, "/");
	print_not_a_valid_identifier(inst, arg);
}

void	unset_tilde_slash_something(t_inst *inst, char *arg)
{
	char *home_value;
	char *hold_str_for_me;

	home_value = getenv("HOME");
	if (home_value == NULL)
	{
		inst->exit_status = 1;
		error_exit(-5);
	}
	hold_str_for_me = ft_substr(arg, 1, ft_strlen(arg) - 1);
	free(arg);
	arg = ft_strjoin(home_value, hold_str_for_me);
	print_not_a_valid_identifier(inst, arg);
}

int	unset_tilde_minus(t_inst *inst, char *arg)
{
	char *old_pwd;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	free(arg);
	arg = ft_strdup(old_pwd);
	print_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_minus_slash(t_inst *inst, char *arg)
{
	char *old_pwd;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	free(arg);
	arg = ft_strjoin(old_pwd, "/");
	print_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_minus_slash_something(t_inst *inst, char *arg)
{
	char *old_pwd;
	char *hold_str_for_me;

	old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
	if (old_pwd == NULL)
	{
		print_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	hold_str_for_me = ft_substr(arg, 2, ft_strlen(arg) - 1);
	free(arg);
	arg = ft_strjoin(old_pwd, hold_str_for_me);
	print_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_plus(t_inst *inst, char *arg)
{
	char *pwd;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	free(arg);
	arg = ft_strdup(pwd);
	print_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_plus_slash(t_inst *inst, char *arg)
{
	char *pwd;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	free(arg);
	arg = ft_strjoin(pwd, "/");
	print_not_a_valid_identifier(inst, arg);
	return (0);
}

int	unset_tilde_plus_slash_something(t_inst *inst, char *arg)
{
	char *pwd;
	char *hold_str_for_me;

	pwd = ft_get_env_value("PWD", inst->env_head);
	if (pwd == NULL)
	{
		print_not_a_valid_identifier(inst, arg);
		return (inst->exit_status);
	}
	hold_str_for_me = ft_substr(arg, 2, ft_strlen(arg) - 1);
	free(arg);
	arg = ft_strjoin(pwd, hold_str_for_me);
	print_not_a_valid_identifier(inst, arg);
	return (0);
}

unsigned int	env_name_is_not_correct(char *str)
{
	int 	i;

	i = 0;
	if (str[i] == 59 && str[1] == '\0')
		return (2);
	else if (str[i] == 59 && str[1] != '\0')
		return (0);
	else if (str[i] == 95 && str[1] == '\0')
		return (2);
	else if (str[i] == 95 && str[1] != '\0')
		return (0);
	else if (str[i] == 126 && str[1] == '\0')
		return (3);
	else if (str[i] == 126 && str[1] == '/' && str[2] == '\0')
		return (4);
	else if (str[i] == 126 && str[1] == '/' && str[2] != '\0')
		return (5);
	else if (str[i] == 126 && str[1] == '-' && str[2] == '\0')
		return (6);
	else if (str[i] == 126 && str[1] == '-' && str[2] == '/' && str[3] == '\0')
		return (7);
	else if (str[i] == 126 && str[1] == '-' && str[2] == '/' && str[3] != '\0')
		return (8);
	else if (str[i] == 126 && str[1] == '+' && str[2] == '\0')
		return (9);
	else if (str[i] == 126 && str[1] == '+' && str[2] == '/' && str[3] == '\0')
		return (10);
	else if (str[i] == 126 && str[1] == '+' && str[2] == '/' && str[3] != '\0')
		return (11);
	else if (str[i] == 33 || (str[i] >= 35 && str[i] <= 38)
	|| (str[i] >= 40 && str[i] <= 59) || (str[i] == 61)
	|| (str[i] >= 63 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 94)
	|| (str[i] == 123) || (str[i] == 125))
		return (0);
	i++;
	while (str[i] != '\0')
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			i++;
		else
			return (0);
	}
	return (1);
}

void	initialize_variables_for_unset(t_inst *inst, t_unset *u)
{
	u->i = 0;
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

int		unset(t_inst *inst, char **args)
{
	t_unset u;

	initialize_variables_for_unset(inst, &u);
	if (args[0] != NULL)
	{
		while (args[u.i] != NULL)
		{
			if (env_name_is_not_correct(args[u.i]) == 0)
				print_not_a_valid_identifier(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.semicolon)
				return (inst->exit_status);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde)
				unset_tilde(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde_slash)
				unset_tilde_slash(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde_slash_something)
				unset_tilde_slash_something(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde_minus)
				inst->exit_status = unset_tilde_minus(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde_minus_slash)
				inst->exit_status = unset_tilde_minus_slash(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde_minus_slash_something)
				inst->exit_status = unset_tilde_minus_slash_something(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde_plus)
				inst->exit_status = unset_tilde_plus(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde_plus_slash)
				inst->exit_status = unset_tilde_plus_slash(inst, args[u.i]);
			else if (env_name_is_not_correct(args[u.i]) == u.tilde_plus_slash_something)
				inst->exit_status = unset_tilde_plus_slash_something(inst, args[u.i]);
			else
			{
				u.error_check = ft_unset_env_var(args[0], inst->env_head);
				if (u.error_check == 0)
					inst->exit_status = 1;
			}
			u.i++;
		}
	}
	return (inst->exit_status);
}
