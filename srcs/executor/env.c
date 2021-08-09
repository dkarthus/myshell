#include "../../includes/minishell.h"

void	assign_a_value(t_tkn *tkn, int i)
{
	if (tkn->cmd[i] == 'E')
	{
		tkn->cmd[i] = 'e';
		i++;
	}
	else if (tkn->cmd[i] == 'N')
	{
		tkn->cmd[i] = 'n';
		i++;
	}
	else if (tkn->cmd[i] == 'V')
	{
		tkn->cmd[i] = 'v';
		i++;
	}
}

static int	check_letter_and_length(t_tkn *tkn, int i)
{
	if (tkn->cmd[i] == 'e' || (tkn->cmd[i] == 'E'
			&& ft_strlen(tkn->cmd) == 3))
		return (0);
	else if (tkn->cmd[i] == 'n' || (tkn->cmd[i] == 'N'
			&& ft_strlen(tkn->cmd) == 3))
		return (0);
	else if (tkn->cmd[i] == 'v' || (tkn->cmd[i] == 'V'
			&& ft_strlen(tkn->cmd) == 3))
		return (0);
	else
		return (1);
}

int	check_the_case(t_tkn *tkn, int i)
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

int	check_env(t_tkn *tkn)
{
	int		i;

	i = 0;
	while (tkn->cmd[i] != '\0')
	{
		if (check_the_case(tkn, i) == 1)
			return (1);
		i++;
	}
	if (check_cmd(tkn, "env") == 1)
		return (1);
	return (0);
}

int	env(t_inst *inst)
{
	t_env	*env;

	env = *(inst->env_head);
	while (env->next != NULL)
	{
		if (ft_strchr(env->line, '=') != NULL)
		{
			write(1, env->line, ft_strlen(env->line));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	if (ft_strchr(env->line, '=') != NULL)
	{
		write(1, env->line, ft_strlen(env->line));
		write(1, "\n", 1);
	}
	return (0);
}
