#include "../../includes/parser.h"

/*
 * Func for shrinking whitespaces in input line into one
 *
 * @param	src main parser struck -> check header parser.h;
 * @return	N/A;
 */
void	skip_wspace(t_src *src)
{
	if (ft_isspace(src->str[src->pos]))
	{
		while (ft_isspace(src->str[src->pos]))
			src->pos++;
		src->args_cnt++;
	}
}

/*
 *	Prints error msg and closes fds;
 *	@param err msg to print;
 *	@param pipe_fd to close;
 *	@param fd to close;
 *	@returns 1 always;
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
