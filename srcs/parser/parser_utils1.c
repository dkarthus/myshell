#include "../../includes/parser.h"

/*
 * Utility func just for shrink down ft_redir_out and ft_redir_in sizes;
 * @param src parsers master struct;
 * @param redir type of redirect;
 * @return 0 = OK, 1 = KO malloc error
 */
static int	ft_redir_util1(t_src *src, char *redir)
{
	if (src->str[src->pos + 1] == redir[0])
	{
		src->args[src->args_cnt] = ft_strdup(redir);
		src->pos = src->pos + 2;
	}
	else
	{
		src->args[src->args_cnt] = ft_strdup(&redir[1]);
		src->pos++;
	}
	if (!src->args[src->args_cnt])
		return (1);
	return (0);
}

/*
 * Utility func just for shrink down ft_redir_out and ft_redir_in sizes;
 * @param src parsers master struct;
 * @param redir type of redirect;
 * @return 0 = OK, 1 = KO malloc error
 */
static int	ft_redir_util2(t_src *src, char *redir)
{
	src->args_cnt++;
	if (src->str[src->pos + 1] == redir[0])
	{
		src->args[src->args_cnt] = ft_strdup(redir);
		src->pos = src->pos + 2;
	}
	else
	{
		src->args[src->args_cnt] = ft_strdup(redir[1]);
		src->pos++;
	}
	if (!src->args[src->args_cnt])
		return (1);
	return (0);
}

/*
 * Parse redirect out >> symbols and adds them into srcs struct args string
 * @param	src parser master struct whos args str will be updated
 * @return	0 = OK, 1 = KO malloc error
 */
int	ft_redir_out(t_src *src)
{
	if (src->args[src->args_cnt] == 0)
	{
		if (ft_redir_util1(src, ">>"))
			return (ft_err_parser("Malloc error", src, NULL, NULL));
	}
	else
	{
		if (ft_redir_util2(src, ">>"))
			return (ft_err_parser("Malloc error", src, NULL, NULL));
	}
	return (0);
}

/*
 * Parse redirect in << symbols and adds them into srcs struct args string
 * @param	src parser master struct whos args str will be updated
 * @return	0 = OK, 1 = KO malloc error
 */
int	ft_redir_in(t_src *src)
{
	if (src->args[src->args_cnt] == 0)
	{
		if (ft_redir_util1(src, "<<"))
			return (ft_err_parser("Malloc error", src, NULL, NULL));
	}
	else
	{
		if (ft_redir_util2(src, "<<"))
			return (ft_err_parser("Malloc error", src, NULL, NULL));
	}
	return (0);
}
