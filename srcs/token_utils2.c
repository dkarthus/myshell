#include "../includes/parser.h"

/*
 *
 */
int ft_is_pipe_tkn(t_tkn *tkn, t_src *src, int *i)
{
	char *tmp;

	tmp = src->args[*i];
	if (!tmp)
		return (0);
	if (tmp[1] == '|' || (!tmp[1] && !(tmp + 1)) || ((tmp + 1) && (tmp + 1)
			[0] == '|'))
		return (ft_err_parser("Syntax error", src, NULL, NULL));
	tkn->is_pipe = 1;
	printf("pipe update\n");
	src->args[*i] = ft_strdup(&src->args[*i][1]);
	free(tmp);
	tmp = NULL;
	return (0);
}

/*
 *
 */
int	ft_ch_symbl(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
