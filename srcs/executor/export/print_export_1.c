#include "../../../includes/minishell.h"

static void	print_else(t_env *env)
{
	printf("declare -x %s", env->key);
	printf("=\"%s\"\n", env->value);
}

t_env	*print_else_2(t_env *env)
{
	if (env->value[0] != '\0')
		print_else(env);
	env = env->next;
	return (env);
}

void	print_if(t_env *env)
{
	if (ft_strchr(env->line, '=') != NULL)
	{
		if (env->value[0] == '\0')
			printf("declare -x %s=\"\"\n", env->key);
		else
			print_else(env);
	}
	else
	{
		if (env->value[0] == '\0')
			printf("declare -x %s\n", env->key);
		else
			print_else(env);
	}
}
