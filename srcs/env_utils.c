#include "../includes/minishell.h"
/*
 * Finds and returns value from linked list of envs vars all accroding the key
 *
 * @param key to find in list;
 * @param head of linked list;
 * @return allocated array with value in it, return NULL if didnt find anything;
 */
char *ft_get_env_value(char *key, t_env **head)
{
	t_env *iter;

	iter = *head;
	while(iter)
	{
		if (ft_strncmp(key, iter->key, ft_strlen(key)) == 0)
			return (iter->value);
		iter = iter->next;
	}
	return (NULL);
}

/*
 * Deletes a var from a vars linked list;
 *
 * @param key to delete;
 * @param head of linked list of envs vars;
 * @return 1 if var found ant destroyed, 0 otherwise;
 */
int	ft_unset_env_var(char *key, t_env **head)
{
	t_env	*iter;
	t_env	*tmp;

	iter = *head;
	if (ft_strncmp(key, iter->key, ft_strlen(key)) == 0)
	{
		*head = iter->next;
		ft_del_elem(iter);
		return (1);
	}
	while (iter->next)
	{
		if (ft_strncmp(key, iter->next->key, ft_strlen(key)) == 0)
		{
			tmp = iter->next;
			iter->next = iter->next->next;
			ft_del_elem(tmp);
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

/*
 * Groups list of envs in 2d massive for passing down to execed binaries
 *
 * @param head of two-way linked list of envs vars;
 * @return double pointer to a 2d array of grouped envs vars or NULL for
 * malloc err;
 */
char **ft_group_envs(t_env **head)
{
	t_env	*tmp;
	char	**envs;
	int		amt;

	tmp = *head;
	amt = 0;
	while(tmp)
	{
		amt++;
		tmp = tmp->next;
	}
	envs = ft_calloc(sizeof(char *), (amt + 1));
	if (!envs)
		return (NULL);
	amt = 0;
	tmp = *head;
	while(tmp)
	{
		envs[amt] = ft_strdup(tmp->line);
		if (!envs[amt])
			return (NULL);
		tmp = tmp->next;
		amt++;
	}
	return (envs);
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

	while(*head)
	{
		tmp = (*head)->next;
		free((*head)->key);
		free((*head)->value);
		free((*head)->line);
		(*head)->key = NULL;
		(*head)->value = NULL;
		(*head)->line = NULL;
		free((*head));
		(*head) = tmp;
	}
	free(head);
	head = NULL;
}
