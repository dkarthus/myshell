#include "../../../includes/minishell.h"

int	is_a_directory(t_inst *inst)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (check_cmd(inst, tkn->cmd) == 0)
		printf("minishell: %s: is a directory\n", tkn->cmd);
	return (0);
}

void	real_substitution(t_inst *inst, int check)
{
	char	*home_value;
	char	*hold_str_for_me;
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	home_value = getenv("HOME");
	if (home_value == NULL)
		error_exit(-5);
	if (check == 0)
	{
		free(tkn->cmd);
		tkn->cmd = ft_strdup(home_value);
	}
	else if (check == 1)
	{
		free(tkn->cmd);
		tkn->cmd = ft_strjoin(home_value, "/");
	}
	else if (check == 2)
	{
		hold_str_for_me = ft_substr(tkn->cmd, 1, ft_strlen(tkn->cmd) - 1);
		free(tkn->cmd);
		tkn->cmd = ft_strjoin(home_value, hold_str_for_me);
		free(hold_str_for_me);
	}
}

int	substitute_tilde(t_inst *inst, int check)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (check == 0)
		real_substitution(inst, check);
	else if (check == 1)
		real_substitution(inst, check);
	else if (check == 2)
		real_substitution(inst, check);
	if (chdir(tkn->cmd) == 0)
		return (0);
	return (1);
}

int	it_is_a_directory_there(t_inst *inst)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (ft_strncmp(tkn->cmd, "~", ft_strlen(tkn->cmd)) == 0)
		return (substitute_tilde(inst, 0));
	else if (ft_strncmp(tkn->cmd, "~/", ft_strlen(tkn->cmd)) == 0)
		return (substitute_tilde(inst, 1));
	else if (tkn->cmd[0] == '~' && tkn->cmd[1] == '\0')
		return (substitute_tilde(inst, 2));
	else if (ft_strncmp(tkn->cmd, "/", ft_strlen(tkn->cmd)) == 0)
		return (0);
	else if (chdir(tkn->cmd) == 0)
		return (0);
	else if (chdir(tkn->cmd) == -1)
		return (no_such_file_or_directory_1(0, tkn->cmd));
	return (1);
}
