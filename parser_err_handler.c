#include "parser.h"

/*
 * Func prints ERR MSG, frees all received params and returns 1;
 */
int ft_err_parser(const char *str, t_src *src, char *to_free1, char *to_free2)
{
	if (str)
		printf("%s\n", str);
	if (src)
	{
		free(src->str);
		src->str = NULL;
		free(src->args);
		src->args = NULL;
	}
	free(to_free1);
	to_free1 = NULL;
	free(to_free2);
	to_free2 = NULL;
	return (1);
}
