#include "../../includes/parser.h"

/*
 * Func check if "to read from" or "to write to" file exists
 * @param	str name of the file;
 * @param	mode 1 standard mode, 2 here_doc no need to check - blank mode;
 * @param	src described in parser.h;
 * @returns 0 = True, 1 = False (=
 */
static int	ft_try_exist(char *str, int mode, t_src *src)
{
	int	fd;

	if (mode == 1)
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
			return (ft_err_parser("\033[90mCouldn't "
					"open file\033[0m", src, NULL, NULL));
		close(fd);
	}
	else
		ft_here_doc(NULL, str, 0);
	return (0);
}

/*
 *	Utilty function for in redirect, checks if file exists;
 *	@param	src described in parser.h;
 *	@param	arg_iter cont of src->args = active argument;
 *	@returns 1 = KO, 0 = OK;
 */
int	ft_blank_check_file(t_src *src, int *arg_iter)
{
	int	i;

	i = 1;
	if (src->args[*arg_iter][i] == '<')
		i++;
	if (src->args[*arg_iter][i] == 0)
	{
		(*arg_iter)++;
		if (!src->args[*arg_iter] || ft_ch_symbl(src->args[*arg_iter][0]))
			return (ft_err_parser("Syntax error", src, NULL, NULL));
		if (ft_try_exist(src->args[*arg_iter], i, src))
			return (1);
	}
	else
	{
		if (ft_ch_symbl(src->args[*arg_iter][i]))
			return (ft_err_parser("\033[90mSyntax "
					"error\033[0m", src, NULL, NULL));
		if (ft_try_exist(&src->args[*arg_iter][i], i, src))
			return (1);
	}
	(*arg_iter)++;
	return (0);
}

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
