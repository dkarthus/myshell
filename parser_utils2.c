#include "parser.h"

/*
 *
 */
static int	ft_append_arg(t_src *src, int *start, int *len)
{
	char *arg;
	char *tmp;

	arg = ft_substr(src->str, *start, *len);
	tmp = src->args[src->args_cnt];
	src->args[src->args_cnt] = ft_strjoin(src->args[src->args_cnt], arg);
	if (!(src->args[src->args_cnt]))
		return (ft_err_parser("Malloc error in parser", src, arg, tmp));
	*start = src->pos;
	*len = 0;
	free (arg);
	free (tmp);
	arg = NULL;
	tmp = NULL;
	return (0);
}

/*
 *
 * @param src main parser struck -> check header parser.h;
 */
int	ft_double_qt(t_src *src, t_env **head)
{
	int		start;
	int		len;

	len = 0;
	start = ++src->pos;
	if (!(src->args[src->args_cnt]))
		src->args[src->args_cnt] = ft_strdup("");
	while (src->str[src->pos] != '\"')
	{
		if (src->str[src->pos] == 0)
			return (ft_err_parser("Unclosed double quotes", src, NULL, NULL));
		if (src->str[src->pos] == '$')
		{
			if (ft_append_arg(src, &start, &len) || ft_dolla(src, head))
				return (1);
		}
		len++;
		src->pos++;
	}
	ft_append_arg(src, &start, &len);
	src->pos++;
	return (0);
}
