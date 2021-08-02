#include "../../includes/minishell.h"

void	unset(t_inst *inst, char **args)
{
	int 	error_check;

	error_check = ft_unset_env_var(args[0], inst->env_head);
	if (error_check == 0)
		printf("key was not found\n");
}
