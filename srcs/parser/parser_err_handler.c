#include "../../includes/parser.h"

/*
 * Func prints ERR MSG, frees all received params and returns 1;
 */
int ft_err_parser(const char *str, t_src *src, char *to_free1, char *to_free2)
{
	int i;

	if (str)
		printf("%s\n", str);
	if (src)
	{
		free(src->str);
		src->str = NULL;
		i = 0;
		while(src->args[i])
		{
			free(src->args[i]);
			src->args[i] = NULL;
			i++;
		}
		free(src->args);
	}
	free(to_free1);
	to_free1 = NULL;
	free(to_free2);
	to_free2 = NULL;
	return (1);
}
