#include "../includes/parser.h"

/*
 *
 */
/*
static int ft_get_fd(char *file, int mode)
{
	int fd;

	if (mode == 1)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(file, O_RDWR | O_CREAT |O_APPEND, 0666);
	return (fd);
}

*/
/*
 *
 *//*

int	ft_update_token_fdin(t_tkn *tkn, t_src *src, int *arg_iter)
{
	int	i;

	i = 1;
	if (tkn->fd_in != 1)
		close(tkn->fd_in);
	if (src->args[*arg_iter][i] == '>')
		i++;
	if (src->args[*arg_iter][i] == '\0')
	{
		(*arg_iter)++;
		if (ft_ch_symbl(src->args[*arg_iter][0]))
			return (ft_err_parser("Parser error near token", src, NULL, NULL));
		tkn->fd_out = ft_get_fd(src->args[*arg_iter], i);
		if (tkn->fd_out == -1)
			return (ft_err_parser("Couldn't access file", src, NULL, NULL));
	}
	else
	{
		if (ft_ch_symbl(src->args[*arg_iter][i]))
			return (ft_err_parser("Parser error near token", src, NULL, NULL));
		tkn->fd_out = ft_get_fd(&src->args[*arg_iter][i], i);
		if (tkn->fd_out == -1)
			return (ft_err_parser("Couldn't access file", src, NULL, NULL));
	}
	return (0);
}
*/


