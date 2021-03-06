#include "../../includes/minishell.h"

static void	assign_a_value(t_tkn *tkn, int i)
{
	if (tkn->cmd[i] == 'P')
	{
		tkn->cmd[i] = 'p';
		i++;
	}
	else if (tkn->cmd[i] == 'W')
	{
		tkn->cmd[i] = 'w';
		i++;
	}
	else if (tkn->cmd[i] == 'D')
	{
		tkn->cmd[i] = 'd';
		i++;
	}
}

static int	check_letter_and_length(t_tkn *tkn, int i)
{
	if (tkn->cmd[i] == 'p' || (tkn->cmd[i] == 'P'
			&& ft_strlen(tkn->cmd) == 3))
		return (0);
	else if (tkn->cmd[i] == 'w' || (tkn->cmd[i] == 'W'
			&& ft_strlen(tkn->cmd) == 3))
		return (0);
	else if (tkn->cmd[i] == 'd' || (tkn->cmd[i] == 'D'
			&& ft_strlen(tkn->cmd) == 3))
		return (0);
	else
		return (1);
}

static int	check_the_case(t_tkn *tkn, int i)
{
	if (check_letter_and_length(tkn, i) == 0)
	{
		assign_a_value(tkn, i);
		i++;
	}
	else if (check_letter_and_length(tkn, i) == 0)
	{
		assign_a_value(tkn, i);
		i++;
	}
	else if (check_letter_and_length(tkn, i) == 0)
	{
		assign_a_value(tkn, i);
		i++;
	}
	else
		return (1);
	return (0);
}

int	check_pwd(t_tkn *tkn)
{
	int		i;

	i = 0;
	while (tkn->cmd[i] != '\0')
	{
		if (check_the_case(tkn, i) == 1)
			return (1);
		i++;
	}
	if (check_cmd(tkn, "pwd") == 1)
		return (1);
	return (0);
}

int	pwd(t_inst	*inst)
{
	char	dir[2048];
	char	*error_check_char_p;
	int		error_check_int;
	char	*pwd;

	error_check_char_p = getcwd(dir, 2048);
	if (error_check_char_p == NULL)
	{
		error_exit(inst->fd_out_save, -2);
		return (g_exit_status);
	}
	pwd = ft_strjoin("PWD=", dir);
	error_check_int = ft_add_env_elem(pwd, inst->env_head);
	free(pwd);
	if (error_check_int == 0)
		error_exit(inst->fd_out_save, -4);
	error_check_char_p = ft_strjoin(error_check_char_p, "\n");
	ft_putstr_fd(error_check_char_p, 1);
	free(error_check_char_p);
	return (0);
}
