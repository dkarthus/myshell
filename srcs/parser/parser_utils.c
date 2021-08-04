#include "../../includes/parser.h"

/*
 * Checks if the symbol is one that needs to be interpret;
 *
 * @param c symbol to check;
 * @return 1 if true, 0 if false
 */
int	ft_check_symbol(char c)
{
	return (c == ' ' || c == '\'' || c == '\"' || c == '$' || c == '<' || c
	=='>' || c == '|' || c == '\0');
}

/*
 *
 */
static int ft_append_arg( t_src *src, char *str, int *start, int *len)
{
	char *arg;
	char *tmp;

	arg = ft_substr(str, *start, *len);
	tmp = src->args[src->args_cnt];
	src->args[src->args_cnt] = ft_strjoin(src->args[src->args_cnt], arg);
	if (!(src->args[src->args_cnt]))
		return (ft_err_parser("Malloc error in parser", src, arg, tmp));
	free (arg);
	free (tmp);
	arg = NULL;
	tmp = NULL;
	return (0);
}

/*
 *
 */
static int ft_dissect_value(t_src *src, char *value)
{
	int i;
	int len;
	int start;

	start = 0;
	i = 0;
	len = 0;
	while (value[i])
	{
		if (ft_isspace(value[i]))
		{
			if (ft_append_arg(src, value, &start, &len))
				return (1);
			while (ft_isspace(value[i]))
				i++;
			start = i;
			len = 0;
		}
		i++;
		len++;
	}
	if (ft_append_arg(src, value, &start, &len))
		return (1);
	return (0);
}

/*
 * Parser execs this func when encounters dollar sign $, func finds a value
 * corresponded to a key after $ and copies it in args str in other case
 * skips $key entirely;
 *
 * @param src parsers main struct -> check header parser.h;
 * @param head of linked list of env vars;
 * @return returns 0 - no errors, and 1 on malloc mistake;
 */
int ft_dolla(t_src *src, t_env **head, int *upstart)
{
	int		start;
	int		len;
	char	*key;
	char	*value;

	src->pos++;
	start = src->pos;
	len = 0;
	while (!(ft_check_symbol(src->str[src->pos])))
	{
		src->pos++;
		len++;
	}
	if (upstart)
		*upstart = src->pos;
	key = ft_substr(src->str, start, len);
	if (!(key))
		return (ft_err_parser("Malloc error in parser", src, NULL, NULL));
	value = ft_get_env_value(key, head);
	if (!value)
		return (!ft_err_parser(NULL, NULL, key, NULL));
	if (!src->args[src->args_cnt])
		src->args[src->args_cnt] = ft_strdup("");
	if (ft_dissect_value(src, value))
		return (ft_err_parser(NULL, src, key, NULL));
	ft_err_parser(NULL, NULL, key, NULL);
	return (0);
}
