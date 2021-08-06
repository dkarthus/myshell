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
