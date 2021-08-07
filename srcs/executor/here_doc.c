#include "../../includes/minishell.h"

/*
 *
 */
int	ft_closefd(char *err, int *pipe_fd, int fd)
{
	if (err)
		printf("%s\n", err);
	if (pipe_fd)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (fd > 0)
		close(fd);
	return (1);
}

/*
 *
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
 *
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
 *
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
		ft_append(&ret, line);
	}
	if (ret)
		ft_putstr_fd(ret, fd_out);
	close(fd_out);
	return (0);
}

/*
 *
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
		waitpid(pid, &ret, 0);
		ft_exit_status_upd(ret);
		close(pipe_fd[1]);
		if (mode == -1)
		{
			if (dup2(pipe_fd[0], 0) == -1)
				ft_putstr_fd("child dup fd0\n", inst->fd_in_save);
		}
		close(pipe_fd[0]);
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
