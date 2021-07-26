#include "minishell.h"

/*
 *
 */
char **ft_group_envs(t_env **head)
{
	t_env	*tmp;
	char **envs;

	tmp = *head;
	while(tmp)
	{

		tmp = tmp->next;
	}
}

/*
 * Func parses env vars and converts them in two-way linked list;
 *
 * @param env 2d array on env vars;
 * @return head of two-way linked list of env vars or NULL on malloc err;
 */
t_env	**ft_parse_env(char *env[])
{
	int	i;
	t_env **head;

	head = malloc(sizeof(t_env *));
	if (!head)
		return (NULL);
	*head = NULL;
	i = 0;
	while (env[i])
	{
		if (!(ft_add_env_elem(env[i], head)))
			return (NULL);
		i++;
	}
	return (head);
}

/*
 * Free two-way linked list of env vars;
 *
 * @param head of linked list of env vars;
 * @return N/A;
 */
void	ft_free_env(t_env **head)
{
	t_env *tmp;

	tmp = *head;
	while(tmp->next)
	{
		free(tmp->key);
		free(tmp->value);
		free(tmp->line);
		free(tmp->prev);
		tmp->key = NULL;
		tmp->value = NULL;
		tmp->line = NULL;
		tmp->prev = NULL;
		tmp = tmp->next;
	}
	free(tmp->key);
	free(tmp->value);
	free(tmp->line);
	free(tmp->prev);
	tmp->key = NULL;
	tmp->value = NULL;
	tmp->line = NULL;
	tmp->prev = NULL;
	free(tmp);
	free(head);
}
