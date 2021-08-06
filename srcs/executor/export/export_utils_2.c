#include "../../../includes/minishell.h"

int	export_comment_symbol(t_inst *inst)
{
	print_export(inst);
	return (0);
}

char	*ft_get_env_key(char *key, t_env **head)
{
	t_env *iter;

	iter = *head;
	while(iter)
	{
		if (ft_strncmp(key, iter->key, ft_strlen(iter->key)) == 0)
			return (iter->key);
		iter = iter->next;
	}
	return (NULL);
}

int	export_var(t_inst *inst, t_u_e *e, char *next_arg)
{
	e->error_check = ft_add_env_elem(next_arg, inst->env_head);
		if (e->error_check == 0)
		{
			exit_status = 1;
			return (exit_status);
		}
	return (exit_status);
}