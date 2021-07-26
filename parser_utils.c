#include "parser.h"


/*
 * Parser execs this func when encounters single quotes '
 *
 * @param src parsers struct;
 * @return returns 0 on success, and 1 when quotes are not closed;
 */
int ft_single_qt(t_src *src)
{
	int		start;
	int		len;
	char	*arg;
	char	*tmp;

	len = 0;
	src->pos++;
	start = src->pos;
	while (src->str[src->pos] != '\'')
	{
		if (src->str[src->pos] == 0)
			return (ft_err_parser("Unclosed single quotes", src, NULL, NULL));
		src->pos++;
		len++;
	}
	src->str[src->pos] = ' ';
	arg = ft_substr(src->str, start, len);
	if (!arg)
		return (ft_err_parser("Malloc error while parsing", src, NULL, NULL));
	tmp = src->ref_str;
	src->ref_str = ft_strjoin(src->ref_str, arg);
	if (!src->ref_str)
		return (ft_err_parser("Malloc error while parsing", src, tmp, arg));
	ft_err_parser(NULL, NULL, tmp, arg);
	src->pos++;
	return (0);
}
static void ft_init_src(t_src *src, char *line)
{
	src->str = line;
	src->pos = 0;
	src->len = ft_strlen(line);
	src->ref_str = ft_strdup("");
}
int main(void)
{
	t_src src;
	char kkk[] = {"'qwert' 'lk"};

	ft_init_src(&src, kkk);
	printf("%s\n", src.str);
	ft_single_qt(&src);
	printf("out %s\n", src.ref_str);
}