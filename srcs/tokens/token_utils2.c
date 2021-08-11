#include "../../includes/parser.h"

/*
 * Process pipe symbol '|', adds it to a new token;
 * @param	tkn newly created token to add to;
 * @param	src described in parser.h;
 * @param	i src->args count;
 * @returns 0 = OK, 1 = KO malloc error;
 */
int	ft_is_pipe_tkn(t_tkn *tkn, t_src *src, int *i)
{
	char	*tmp;

	tmp = src->args[*i];
	if (!tmp)
		return (0);
	if (tmp[1] == '|' || (!tmp[1] && !(tmp + 1)) || ((tmp + 1) && (tmp + 1)
			[0] == '|'))
		return (ft_err_parser("Syntax error", src, NULL, NULL));
	tkn->is_pipe = 1;
	if (tmp[1] != 0)
	{
		src->args[*i] = ft_strdup(&src->args[*i][1]);
		free(tmp);
	}
	else
		(*i)++;
	tmp = NULL;
	return (0);
}

/*
 *	Small util funcs check if char is '|' '<' '>'
 *	@param c char to check
 *	@returns 1 =true, 0 = false
 */
int	ft_ch_symbl(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
