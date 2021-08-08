#include "../../../includes/minishell.h"

static t_env	*print_key(t_env *env)
{
	printf("declare -x %s\n", env->key);
	env = env->next;
	return (env);
}

static t_env	*print_key_equal_double_quotes(t_env *env)
{
	printf("declare -x %s=\"\"\n", env->key);
	env = env->next;
	return (env);
}

void	print_export(t_inst *inst)
{
	t_env	*env;

	env = *(inst->env_head);
	while (env->next != NULL)
	{
		if (ft_strchr(env->line, '=') != NULL)
		{
			if (env->value[0] == '\0')
			{
				env = print_key_equal_double_quotes(env);
				continue ;
			}
			env = print_else_2(env);
		}
		else
		{
			if (env->value[0] == '\0')
			{
				env = print_key(env);
				continue ;
			}
			env = print_else_2(env);
		}
	}
	print_if(env);
}
