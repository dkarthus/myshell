#include "../../includes/minishell.h"

/*
 *	Frees str arrays in right order and nulls them, also prints error msg;
 *	@param	print	error msg to print;
 *	@param	str array to free;
 *	@returns 0;
 */
static char	**ft_free(char *print, char **str, int fd_out_save)
{
	int	i;

	if (print)
		ft_putstr_fd(print, fd_out_save);
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
static char	**ft_combine(char *name, char **spl_path, int save)
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
			return (ft_free("\033[90mMalloc error\033[0m\n", spl_path, save));
		i++;
	}
	free(spl_path[i - 1]);
	spl_path[i - 1] = ft_strdup(name);
	if (!spl_path[i - 1])
		return (ft_free("\033[90mMalloc error\033[0m\n", spl_path, save));
	return (spl_path);
}

/*
 *	Probes every path received in **path_combos for existing;
 *	@param path_combos str array of paths to probe to for bin;
 *	@returns NULL bin not found, or path of bin;
 */
static char	*ft_find_bin(char **path_combos, int save)
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
		g_exit_status = 127;
		return (*(ft_free("\033[90mminishell: command not found\n\033[0m",
						path_combos, save)));
	}
	path = ft_strdup(path_combos[i]);
	if (!path)
		return (*(ft_free("\033[90mMalloc error in bin.finder\n\033[0m",
					path_combos, save)));
	ft_free(NULL, path_combos, save);
	return (path);
}

/*
 *	Dissects PATH var and adds bin name to it to create array of possible
 *	locations of binary we trying to exec, then probes them all;
 *	@param	name of binary;
 *	@param	head of the list of env vars;
 *	@returns NULL - KO error, or path to binary soon to be execed;
 */
char	*ft_get_bin_path(char *name, t_inst *inst)
{
	char	*path;
	char	**split_path;
	char	**combos;

	path = ft_get_env_value("PATH", inst->env_head);
	if (!path || !*path)
		return (name);
	split_path = ft_split(path, ':');
	if (!split_path)
	{
		ft_putstr_fd("\033[90mMalloc error\033[0m\n", inst->fd_out_save);
		return (0);
	}
	combos = ft_combine(name, split_path, inst->fd_out_save);
	if (!combos)
		return (0);
	return (ft_find_bin(combos, inst->fd_out_save));
}
