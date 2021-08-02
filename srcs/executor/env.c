#include "../../includes/minishell.h"

void	assign_a_value(t_inst *inst, int i)
{
	t_tkn *tkn;

	tkn = *(inst->tkn_head);
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

static int		check_letter_and_length(t_inst *inst, int i)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
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

int		check_the_case(t_inst *inst, int i)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (check_letter_and_length(inst, i) == 0)
	{
		assign_a_value(inst, i);
		i++;
	}
	else if (check_letter_and_length(inst, i) == 0)
	{
		assign_a_value(inst, i);
		i++;
	}
	else if (check_letter_and_length(inst, i) == 0)
	{
		assign_a_value(inst, i);
		i++;
	}
	else
		return (1);
	return (0);
}

int		check_env(t_inst *inst)
{
	t_tkn	*tkn;
	int 	i;

	i = 0;
	tkn = *(inst->tkn_head);
	while (tkn->cmd[i] != '\0')
	{
		if (check_the_case(inst, i) == 1)
			return (1);
		i++;
	}
	if (check_cmd(inst, "env") == 1)
		return (1);
	return (0);
}

int 	env(t_inst *inst)
{
	t_env *env;

	env = *(inst->env_head);
	while (env->next != NULL)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
	return (0);
}
