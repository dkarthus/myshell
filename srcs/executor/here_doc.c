#include "../../includes/minishell.h"

/*
 *	Prints err msg 'print' and frees all incoming pointers;
 */
static int	ft_fr_ret(char *print, char *str, char *str1, char *str2)
{
	if (print)
		printf("%s\n", print);
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	return (0);
}

/*
 *	Appends strs in array ;
 *	@param	ret str array of input linesl
 *	@param	line to append to ret;
 *	@returns 1 KO error, 0 = OK
 */
static int	ft_append(char **ret, char *line)
{
	char	*tmp;
	char	*tmp1;

	if (!*ret)
	{
		*ret = ft_strjoin(line, "\n");
		if (!*ret)
			return (!ft_fr_ret("Malloc error", NULL, line, NULL));
		return (ft_fr_ret(NULL, NULL, line, NULL));
	}
	tmp = ft_strjoin(line, "\n");
	tmp1 = *ret;
	*ret = ft_strjoin(*ret, tmp);
	if (!*ret)
		return (!ft_fr_ret("Malloc error in parser", tmp, tmp1, line));
	return (ft_fr_ret(NULL, line, tmp, tmp1));
}

/*
 *	Loop for here_doc starts readin new line and adding them to str array, then
 *	pushes them into pipe[1] write end;
 *	@param	fd_out to write to(pipe write end);
 *	@param	stop_word for here_doc util;
 *	@returns 1 KO error, 0 = OK
 */
static int	ft_here_doc_loop(int fd_out, const char *stop_word)
{
	char	*line;
	char	*ret;

	ret = NULL;
	while (21)
	{
		line = readline("> ");
		if (!line)
			return (1);
		if (ft_strncmp(stop_word, line, ft_strlen(stop_word)) == 0)
		{
			free(line);
			break ;
		}
		if (ft_append(&ret, line))
			return (1);
	}
	if (ret)
		ft_putstr_fd(ret, fd_out);
	close(fd_out);
	return (0);
}

/*
 *	Cuts down szie of here_doc func, increase readability;
 */
static int	ft_here_doc_util(int *pipe_fd, int *ret, int pid, int mode)
{
	waitpid(pid, ret, 0);
	ft_exit_status_upd(*ret);
	close(pipe_fd[1]);
	if (mode == -1)
	{
		if (dup2(pipe_fd[0], 0) == -1)
			return (ft_closefd("dup2 error", pipe_fd, -1));
	}
	close(pipe_fd[0]);
	return (0);
}

/*
 * Imitates functionality of here_doc util
 * @param	inst master struct described in minishell.h;
 * @param	stop_word for here_doc;
 * @param	mode -1 statard mode, all else blank mode(dont write to any fd);
 * @returns 0 = OK, 1 = KO error;
 */
int	ft_here_doc(t_inst *inst, const char *stop_w, int mode)
{
	int	pid;
	int	pipe_fd[2];
	int	ret;

	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		return (ft_closefd("Fork error in here_doc", pipe_fd, -1));
	if (pid > 0)
	{
		if (ft_here_doc_util(pipe_fd, &ret, pid, mode))
			return (1);
		return (0);
	}
	if (inst)
	{
		dup2(inst->fd_in_save, 0);
		close(inst->fd_in_save);
	}
	if (ft_here_doc_loop(pipe_fd[1], stop_w))
		return (1);
	exit(0);
}
