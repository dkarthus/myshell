#include "../includes/parser.h"
/*

*/
/*
 *
 *//*

static int ft_exec_here_doc(char *stop_word)
{
	//yet to be done
}
*/

/*
 *
 */
static int	ft_try_exist(char *str, int mode, t_src *src)
{
	int fd;

	if (mode == 1)
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
			return (ft_err_parser("Couldn't open file", src, NULL, NULL));
		close(fd);
	}
/*	else
	{
		if (ft_exec_here_doc(str))
			return (ft_err_parser(NULL, src, NULL, NULL));
	}*/
	return (0);
}

/*
 *
 */
int ft_blank_check_file(t_src *src, int *arg_iter)
{
	int i;

	i = 1;
	if (src->args[*arg_iter][i] == '<')
		i++;
	if (src->args[*arg_iter][i] == 0)
	{
		(*arg_iter)++;
		if (ft_ch_symbl(src->args[*arg_iter][0]))
			return (ft_err_parser("Syntax error", src, NULL, NULL));
		if (ft_try_exist(src->args[*arg_iter], i, src))
			return (1);
	}
	else
	{
		if (ft_ch_symbl(src->args[*arg_iter][i]))
			return (ft_err_parser("Syntax error", src, NULL, NULL));
		if (ft_try_exist(&src->args[*arg_iter][i], i, src))
			return (1);
	}
	(*arg_iter)++;
	return (0);
}

/*
 *
 */
static int ft_get_fd(char *file, int mode)
{
	int fd;

	if (mode == 1)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(file, O_RDWR | O_CREAT |O_APPEND, 0666);
	return (fd);
}

/*
 *
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
	(*arg_iter)++;
	return (0);
}

