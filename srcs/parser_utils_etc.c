#include "../includes/parser.h"

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

/*
 * Check input line if it's good for saving in 'history', meaning
 * if there characters other than whitespaces or if its blank;
 *
 * @param str string input from readline;
 * @return 0 - valid string, 1 - invalid string;
*/
int ft_check_input_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	if (*line == 0)
		return (1);
	while(line[i])
	{
		if (!(ft_isspace(line[i])))
			return (0);
		i++;
	}
	return (1);
}
