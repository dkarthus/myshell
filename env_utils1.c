#include "minishell.h"

/*
 * Creates new elem in two-way linked list of env vars, then fills elems line,
 * key, value with contents by dissecting src;
 *
 * @param src to dissect;
 *@return pointer on created and filled elem or NULL on malloc error;
 */
static t_env	*ft_create_fill_elem(const char *src)
{
	int	i;
	t_env *new_elem;

	new_elem = malloc(sizeof(t_env));
	if (!(new_elem))
		return (NULL);
	i = 0;
	new_elem->line = ft_strdup(src);
	while (src[i] != '=' || src[i] != 0)
		i++;
	new_elem->key = ft_substr(src, 0, i);
	if (src[i] == 0)
		new_elem->value = ft_strdup("");
	else
		new_elem->value = ft_substr(src, i + 1, ft_strlen(src));
	if (!new_elem->line || !new_elem->key || !new_elem->value)
		return (0);
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

/*
 * Updates value of env var and frees old strs
 *
 * @param old_elem with old values;
 * @param new_elem with new values;
 * @return N/A
 */
static void	ft_update_elem(t_env *old_elem, t_env *new_elem)
{
	free(old_elem->value);
	free(old_elem->line);
	free(new_elem->key);
	old_elem->line = new_elem->line;
	old_elem->value = new_elem->value;
	new_elem->key = NULL;
	free(new_elem);
	new_elem = NULL;
}

/*
 * Compares keys on env vars and inserts elems in alphbetical oreder;
 *
 * @param head of two-way linked list of env vars;
 * @param elem to insert in this list;
 * @return N/A;
 */
static void	ft_insert_elem(t_env **head, t_env *elem)
{
	t_env	*iter;

	iter = *head;
	while (ft_strncmp(iter->key, elem->key, ft_strlen(iter->key)) > 0)
	{
		if (!iter->next)
		{
			iter->next = elem;
			return ;
		}
		iter = iter->next;
	}
	if (ft_strncmp(iter->key, elem->key, ft_strlen(iter->key)) == 0)
		ft_update_elem(iter, elem);
	else
	{
		elem->next = iter;
		elem->prev = iter->prev;
		iter->prev = elem;
	}
}

/*
 * Func adds env elem in two-way linked list;
 *
 * @param src env elem that will be converted in list node;
 * @param head of the list;
 *@return 0 on malloc err, otherwise ret >0;
 */
int	ft_add_env_elem(char *src, t_env **head)
{
	t_env	*new_elem;

	if (*head == NULL)
	{
		*head = ft_create_fill_elem(src);
		if (!(*head))
			return (0);
		return (1);
	}
	new_elem = ft_create_fill_elem(src);
	if (!new_elem)
		return (0);
	ft_insert_elem(head, new_elem);
	return (1);
}
