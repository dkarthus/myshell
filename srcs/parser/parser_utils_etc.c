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

/*
 * Checks if the symbol is one that needs to be interpret;
 *
 * @param c symbol to check;
 * @return 1 if true, 0 if false
 */
int	ft_check_symbol(char c, int mode)
{
	if (mode == 1)
	{
		return (c == ' ' || c == '\'' || c == '\"' || c == '$' || c == '<' || c
			=='>' || c == '|' || c == '\0');
	}
	if (mode == 2)
	{
		return (ft_isalpha(c) || c == 95);
	}
	else
	{
		return (ft_isalpha(c) || ft_isalnum(c) || c == 95);
	}
}
