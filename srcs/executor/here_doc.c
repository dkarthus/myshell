#include "../../includes/minishell.h"

/*
 *
 */
static int ft_closefd(char *err, int *pipe_fd, int fd)
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
static int ft_free_and_return(char *print, char *str, char *str1, char *str2)
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
static int ft_append(char **ret, char *line)
{
	char *tmp;
	char *tmp1;

	if (!*ret)
	{
		*ret = ft_strjoin(line, "\n");
		if (!*ret)
			return (1); //(ft_err_parser("Malloc error in parser", NULL, line,NULL));
		return (ft_free_and_return(NULL, NULL, line, NULL));
	}
	tmp = ft_strjoin(line , "\n");
	tmp1 = *ret;
	*ret = ft_strjoin(*ret, tmp);
	if (!*ret)
		return (!ft_free_and_return("Malloc error in parser", tmp, tmp1, line));
	return (ft_free_and_return(NULL, line, tmp, tmp1));
}

/*
 *
 */
static int ft_here_doc_loop(int fd_out, const char *stop_word)
{
	char *line;
	char *ret;

	ret = NULL;
	while (21)
	{
		line = readline("> ");
		if (!line)
			return (1);//(ft_err_parser("Readline error", NULL, NULL, NULL));
		if (ft_strncmp(stop_word, line, ft_strlen(stop_word)) == 0)
		{
			free(line);
			break ;
		}
		ft_append(&ret, line);
	}
	if (ret)
		ft_putstr_fd(ret, fd_out);
	return (0);
}

/*
 *
 */
int	ft_here_doc(const char *stop_w, int mode)
{
	int	pid;
	int	pipe_fd[2];
	int	tmp_stdin;
	int status;

	pipe(pipe_fd);
	tmp_stdin = dup(0);
	if (mode)
		dup2(pipe_fd[0], 0);
	pid = fork();
	if (pid < 0)
		return (ft_closefd("Fork error in here_doc", pipe_fd, tmp_stdin));
	if (pid == 0)
	{
		dup2(tmp_stdin, 0);
		if (ft_here_doc_loop(pipe_fd[1], stop_w))
			return (1);
		ft_closefd(NULL, pipe_fd, tmp_stdin);
		close(0);
		return (0);
	}
	waitpid(pid, &status, 0);
	dup2(tmp_stdin, 0);
	if (!WIFEXITED(status))
		return (WEXITSTATUS(status));
	ft_closefd(NULL, pipe_fd, tmp_stdin);
	return (0);
}