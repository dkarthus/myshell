#include "../../includes/minishell.h"

char *real_unset_arg_substitution(char **args, int check, int i)
{
	char	*home_value;
	char	*hold_str_for_me;
	char	*arg;

	arg = NULL;
	home_value = getenv("HOME");
	if (home_value == NULL)
		error_exit(-5);
	if (check == 0)
	{
		free(args);
		arg = ft_strdup(home_value);
		return (arg);
	}
	else if (check == 1)
	{
		free(args);
		arg = ft_strjoin(home_value, "/");
		return (arg);
	}
	else if (check == 2)
	{
		hold_str_for_me = ft_substr(args[i], 1, ft_strlen(args[i]) - 1);
		free(args);
		arg = ft_strjoin(home_value, hold_str_for_me);
		free(hold_str_for_me);
		return (arg);
	}
	return (NULL);
}

char	*substitute_unset_tilde(char **args, int check, int i)
{
	char	*arg;

	arg = NULL;
	if (check == 0)
	{
		arg = ft_strdup(real_unset_arg_substitution(&args[i], check, i));
		return (arg);
	}
	else if (check == 1)
	{
		arg = ft_strdup(real_unset_arg_substitution(&args[i], check, i));
		return (arg);
	}
	else if (check == 2)
	{
		arg = ft_strdup(real_unset_arg_substitution(&args[i], check, i));
		return (arg);
	}
	return (NULL);
}

int		check_unset_arg(const char *arg, const char *check)
{
	size_t	len;

	len = ft_strlen(check);
	if (ft_strlen(arg) == len
		&& ft_strncmp(arg, check, len) == 0)
		return (0);
	else
		return (1);
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
	else if (str[i] == 33
	|| (str[i] >= 35 && str[i] <= 38)
	|| (str[i] >= 40 && str[i] <= 59)
	|| (str[i] == 61)
	|| (str[i] >= 63 && str[i] <= 64)
	|| (str[i] >= 91 && str[i] <= 94)
	|| (str[i] == 123)
	|| (str[i] == 125))
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

void	unset(t_inst *inst, char **args)
{
	int				error_check;
	unsigned int	semicolon_underscore;
	unsigned int	tilde;
	unsigned int	tilde_slash;
	unsigned int	tilde_slash_something;
	unsigned int	tilde_minus;
	unsigned int	tilde_minus_slash;
	unsigned int	tilde_minus_slash_something;
	unsigned int	tilde_plus;
	unsigned int	tilde_plus_slash;
	unsigned int	tilde_plus_slash_something;

	semicolon_underscore = 2;
	tilde = 3;
	tilde_slash = 4;
	tilde_slash_something = 5;
	tilde_minus = 6;
	tilde_minus_slash = 7;
	tilde_minus_slash_something = 8;
	tilde_plus = 9;
	tilde_plus_slash = 10;
	tilde_plus_slash_something = 11;
	if (args[0] != NULL)
	{
		if (env_name_is_not_correct(args[0]) == 0)
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		else if (env_name_is_not_correct(args[0]) == semicolon_underscore)
			return ;
		else if (env_name_is_not_correct(args[0]) == tilde)
		{
			char	*home_value;

			home_value = getenv("HOME");
			if (home_value == NULL)
				error_exit(-5);
			free(args[0]);
			args[0] = ft_strdup(home_value);
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else if (env_name_is_not_correct(args[0]) == tilde_slash)
		{
			char	*home_value;

			home_value = getenv("HOME");
			if (home_value == NULL)
				error_exit(-5);
			free(args[0]);
			args[0] = ft_strjoin(home_value, "/");
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else if (env_name_is_not_correct(args[0]) == tilde_slash_something)
		{
			char	*home_value;
			char	*hold_str_for_me;

			home_value = getenv("HOME");
			if (home_value == NULL)
				error_exit(-5);
			hold_str_for_me = ft_substr(args[0], 1, ft_strlen(args[0]) - 1);
			free(args[0]);
			args[0] = ft_strjoin(home_value, hold_str_for_me);
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else if (env_name_is_not_correct(args[0]) == tilde_minus)
		{
			char	*old_pwd;

			old_pwd = ft_get_env_value("OLDPWD", inst->env_head);
			if (old_pwd == NULL)
				error_exit(-5);
			free(args[0]);
			args[0] = ft_strdup(home_value);
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else if (env_name_is_not_correct(args[0]) == tilde_minus_slash)
		{
			char	*home_value;

			home_value = getenv("HOME");
			if (home_value == NULL)
				error_exit(-5);
			free(args[0]);
			args[0] = ft_strdup(home_value);
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else if (env_name_is_not_correct(args[0]) == tilde_minus_slash_something)
		{
			char	*home_value;

			home_value = getenv("HOME");
			if (home_value == NULL)
				error_exit(-5);
			free(args[0]);
			args[0] = ft_strdup(home_value);
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else if (env_name_is_not_correct(args[0]) == tilde_plus)
		{
			char	*home_value;

			home_value = getenv("HOME");
			if (home_value == NULL)
				error_exit(-5);
			free(args[0]);
			args[0] = ft_strdup(home_value);
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else if (env_name_is_not_correct(args[0]) == tilde_plus_slash)
		{
			char	*home_value;

			home_value = getenv("HOME");
			if (home_value == NULL)
				error_exit(-5);
			free(args[0]);
			args[0] = ft_strdup(home_value);
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else if (env_name_is_not_correct(args[0]) == tilde_plus_slash_something)
		{
			char	*home_value;

			home_value = getenv("HOME");
			if (home_value == NULL)
				error_exit(-5);
			free(args[0]);
			args[0] = ft_strdup(home_value);
			printf("minishell: unset: `%s': not a valid identifier\n", args[0]);
		}
		else
		{
			error_check = ft_unset_env_var(args[0], inst->env_head);
			if (error_check == 0)
				printf("key was not found\n");
		}

//		while (args[i] != NULL)
//		{
//			if (check_unset_arg(args[i], "~") == 0 && args[i][1] == '\0')
//				arg = ft_strdup(substitute_unset_tilde(&args[i], 0, i));
//			else if (check_unset_arg(args[i], "~/") == 0)
//				arg = ft_strdup(substitute_unset_tilde(&args[i], 1, i));
//			else if (args[i][0] == '~' && args[i][1] == '/' && args[i][2] != '\0')
//				arg = ft_strdup(substitute_unset_tilde(&args[i], 2, i));
//			i++;
//		}
	}
	return ;
}
