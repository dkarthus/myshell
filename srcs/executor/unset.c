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

void	unset(t_inst *inst, char **args)
{
	int 	error_check;
	int 	i;
	char	*arg;

	i = 0;
	arg = NULL;
	if (args[0] != NULL)
	{
		while (args[i] != NULL)
		{
			if (check_unset_arg(args[i], "~") == 0 && args[i][1] == '\0')
				arg = ft_strdup(substitute_unset_tilde(&args[i], 0, i));
			else if (check_unset_arg(args[i], "~/") == 0)
				arg = ft_strdup(substitute_unset_tilde(&args[i], 1, i));
			else if (args[i][0] == '~' && args[i][1] == '/' && args[i][2] != '\0')
				arg = ft_strdup(substitute_unset_tilde(&args[i], 2, i));
			i++;
		}
	error_check = ft_unset_env_var(arg, inst->env_head);
	if (error_check == 0)
		printf("key was not found\n");
	}
	return ;
}
