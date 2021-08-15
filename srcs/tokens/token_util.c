#include "../../includes/parser.h"

/*
 * Adds args that our cmd will be launched with;
 * @param	tkn to add args;
 * @param	src described in parser.h;
 * @param	arg_iter count of src->args;
 * @returns 0 = OK, 1 = KO error;
 */
int	ft_update_args(t_tkn *tkn, t_src *src, int *arg_iter)
{
	int	i;

	if (!tkn->args)
	{
		tkn->args = ft_calloc(sizeof(char *), 255);
		if (!tkn->args)
			return (ft_err_parser("Malloc "
					 "error in parser", src, NULL, NULL));
	}
	i = 0;
	while (tkn->args[i])
		i++;
	tkn->args[i] = ft_strdup(src->args[*arg_iter]);
	if (!tkn->args[i])
		return (ft_err_parser("Malloc "
				"error in parser", src, NULL, NULL));
	(*arg_iter)++;
	return (0);
}

/*
 * Get fd of files to read from, or turns on here_doc flag;
 * @param	file name;
 * @param	mode 1 = <, else << here_doc;
 * @returns fd, -1 fd error;
 */
static int	ft_get_fd(char *str, int mode, t_tkn *tkn)
{
	int	fd;

	if (mode == 1)
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
			return (ft_err_parser("Couldn't "
					"access file", NULL, NULL, NULL));
	}
	else
	{
		fd = -1;
		tkn->is_here_doc = 1;
		tkn->stop_word = ft_strdup(str);
		if (!tkn->stop_word)
			return (ft_err_parser("Malloc "
					  "err in parser", NULL, NULL, NULL));
	}
	return (fd);
}

/*
 * Func process in redirect symbol < and << and adds new tkn accordingly
 * @param	tkn new tkn;
 * @param	src described in parser.h;
 * @param	arg_iter count of args in src->args;
 * @returns 1 = KO and 0 = OK;
 */
int	ft_update_token_fdin(t_tkn *tkn, t_src *src, int *arg_iter)
{
	int	i;

	i = 1;
	if (tkn->fd_in > 0)
		close(tkn->fd_in);
	if (src->args[*arg_iter][i] == '<')
		i++;
	if (src->args[*arg_iter][i] == '\0')
	{
		++(*arg_iter);
		if (!src->args[*arg_iter] || ft_ch_symbl(src->args[*arg_iter][0]))
			return (ft_err_parser("Syntax error near <", src, NULL, NULL));
		tkn->fd_in = ft_get_fd(src->args[*arg_iter], i, tkn);
		if (tkn->fd_in == 1)
			return (ft_err_parser(NULL, src, NULL, NULL));
	}
	else
	{
		if (ft_ch_symbl(src->args[*arg_iter][i]))
			return (ft_err_parser("Syntax error", src, NULL, NULL));
		tkn->fd_in = ft_get_fd(&src->args[*arg_iter][i], i, tkn);
		if (tkn->fd_in == 1)
			return (ft_err_parser(NULL, src, NULL, NULL));
	}
	return (++(*arg_iter) && 0);
}
