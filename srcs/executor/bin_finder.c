#include "../../includes/minishell.h"

/*
 *
 */
static char **ft_free(char *print, char **str)
{
	int	i;

	if (print)
		printf("%s\n", print);
	if (str)
	{
		i = 0;
		while (i < 10)
		{
			free(str[i]);
			str[i] = 0;
			i++;
		}
		free(str);
		str = 0;
	}
	return (0);
}

/*
 *
 */
char **ft_combine(char *name, char **spl_path)
{
	int	i;
	char *tmp;

	i = 0;
	while(spl_path[i])
	{
		tmp = spl_path[i];
		spl_path[i] = ft_strjoin(spl_path[i], "/");
		free(tmp);
		tmp = spl_path[i];
		spl_path[i] = ft_strjoin(spl_path[i], name);
		free(tmp);
		if (!spl_path[i])
			return (ft_free("Malloc error", spl_path));
		i++;
	}
	return (spl_path);
}

/*
 *
 */
static char *ft_find_bin(char **path_combos)
{
	char		*path;
	struct stat	st;
	int			i;

	i = 0;
	while (path_combos[i])
	{
		if (stat(path_combos[i], &st) == 0)
			break ;
		i++;
	}
	if (path_combos[i] == 0)
	{
		ft_free("Couldn't find bin file", path_combos);
		return (0);
	}
	path = ft_strdup(path_combos[i]);
	ft_free(NULL, path_combos);
	return (path);
}

/*
 *
 */
char	*ft_find_binary(char *name, t_env **head)
{
	char *path;
	char **split_path;
	char **combos;

	path = ft_get_env_value("PATH", head);
	if (!path || !*path)
	{
		printf("Please set PATH variable\n");
		return (1);
	}
	split_path = ft_split(path, ':');
	if (!split_path)
	{
		printf("Malloc error\n");
		return (1);
	}
	combos = ft_combine(name, split_path);
	if (!combos)
		return (0);
	return (ft_find_bin(combos));
}