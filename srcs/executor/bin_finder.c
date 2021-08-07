#include "../../includes/minishell.h"

/*
 *	Frees str arrays in right order and nulls them, also prints error msg;
 *	@param	print	error msg to print;
 *	@param	str array to free;
 *	@returns 0;
 */
static char	**ft_free(char *print, char **str)
{
	int	i;

	if (print)
		printf("%s\n", print);
	if (str)
	{
		i = 0;
		while (str[i])
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
 *	Combines paths and name of bin together;
 *	@param	name of binary;
 *	@param spl_path split paths of bin dirs;
 *	@returns NULL - malloc error, str array of split paths;
 */
char	**ft_combine(char *name, char **spl_path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (spl_path[i])
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
	free(spl_path[i - 1]);
	spl_path[i - 1] = ft_strdup(name);
	if (!spl_path[i - 1])
		return (ft_free("Malloc error", spl_path));
	return (spl_path);
}

/*
 *	Probes every path received in **path_combos for existing;
 *	@param path_combos str array of paths to probe to for bin;
 *	@returns NULL bin not found, or path of bin;
 */
static char	*ft_find_bin(char **path_combos)
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
	if (!path)
	{
		ft_free("Malloc error in bin.finder", path_combos);
		return (0);
	}
	ft_free(NULL, path_combos);
	return (path);
}

/*
 *	Dissects PATH var and adds bin name to it to create array of possible
 *	locations of binary we trying to exec, then probes them all;
 *	@param	name of binary;
 *	@param	head of the list of env vars;
 *	@returns NULL - KO error, or path to binary soon to be execed;
 */
char	*ft_get_bin_path(char *name, t_env **head)
{
	char	*path;
	char	**split_path;
	char	**combos;

	path = ft_get_env_value("PATH", head);
	if (!path || !*path)
	{
		printf("Please set PATH variable\n");
		return (0);
	}
	split_path = ft_split(path, ':');
	if (!split_path)
	{
		printf("Malloc error\n");
		return (0);
	}
	combos = ft_combine(name, split_path);
	if (!combos)
		return (0);
	return (ft_find_bin(combos));
}
