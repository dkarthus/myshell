#include "../../includes/parser.h"

/*
 * Get fd of files to write to, creates files if needed;
 * @param	file name;
 * @param	mode 1 = TRUNC, else APPEND;
 * @returns fd, -1 fd error;
 */
static int	ft_get_fd(char *file, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	return (fd);
}

/*
 * Func process out redirect symbol > and >> and adds new tkn accordingly
 * @param	tkn new tkn;
 * @param	src described in parser.h;
 * @param	arg_iter count of args in src->args;
 * @returns 1 = KO and 0 = OK;
 */
int	ft_update_token_fdout(t_tkn *tkn, t_src *src, int *arg_iter)
{
	int	i;

	i = 1;
	if (tkn->fd_out != 1)
		close(tkn->fd_out);
	if (src->args[*arg_iter][i] == '>')
		i++;
	if (src->args[*arg_iter][i] == '\0')
	{
		++(*arg_iter);
		if (!src->args[*arg_iter] || ft_ch_symbl(src->args[*arg_iter][0]))
			return (ft_err_parser("Parser error near >", src, NULL, NULL));
		tkn->fd_out = ft_get_fd(src->args[*arg_iter], i);
		if (tkn->fd_out == -1)
			return (ft_err_parser("Couldn't access file", src, NULL, NULL));
	}
	else
	{
		if (ft_ch_symbl(src->args[*arg_iter][i]))
			return (ft_err_parser("Parser error near >", src, NULL, NULL));
		tkn->fd_out = ft_get_fd(&src->args[*arg_iter][i], i);
		if (tkn->fd_out == -1)
			return (ft_err_parser("Couldn't access file", src, NULL, NULL));
	}
	return (++(*arg_iter) && 0);
}
