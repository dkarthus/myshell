#include "../../includes/parser.h"

/*
 *
 */
static void	ft_util_err_pars(const char *str)
{
	if (str && (str[0] == 'U' || str[0] == 'S'))
		g_exit_status = 258;
	if (str && str[0] == 'C')
		g_exit_status = 1;
}

/*
 * Error handling function for parser, frees all incoming params
 * always returns 1
 */
int	ft_err_parser(const char *str, t_src *src, char *to_free1, char *to_free2)
{
	int	i;

	ft_util_err_pars(str);
	if (str)
		printf("%s\n", str);
	if (src)
	{
		free(src->str);
		src->str = NULL;
		i = 0;
		while (i < 255)
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
