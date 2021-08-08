#include "../../includes/parser.h"
#include "../../includes/minishell.h"

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
 * Appends delimited args to str in src
 * @param src parsers master struct contains args str to be updated here;
 * @param str to append;
 * @param start of argument in str;
 * @param len of argument in str;
 * @return 0 = OK, 1 = KO malloc error
 */
static int	ft_append_arg( t_src *src, char *str, int *start, int *len)
{
	char	*arg;
	char	*tmp;

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
 * Dissects env var value into different args if finds space delimiter
 * @param src parser master struct with args str that we need to update here
 * @param value to be dissected
 * @returns 0 = OK, 1 = KO malloc error;
 */
static int	ft_dissect_value(t_src *src, char *value)
{
	int	i;
	int	len;
	int	start;

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
 *	Func for pulling $? var from global exit_status var;
 *	@param src parsers master struct contains args str that will be modified here
 *	@param upstart offset parameter for correct argument parsing
 *	@returns 1 = KO(malloc error), 0 = OK
 */
static int	ft_exit_status(t_src *src, int *upstart)
{
	char	*ext_st;
	char	*tmp;

	ext_st = ft_itoa(g_exit_status);
	src->pos++;
	if (upstart)
		*upstart = src->pos;
	tmp = src->args[src->args_cnt];
	src->args[src->args_cnt] = ft_strjoin(tmp, ext_st);
	if (!src->args[src->args_cnt])
		return (ft_err_parser("Malloc error", src, NULL, NULL));
	free(tmp);
	free(ext_st);
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
int	ft_dolla(t_src *src, t_env **head, int *upstart)
{
	int		start;
	int		len;
	char	*key;
	char	*value;

	if (++src->pos && !src->args[src->args_cnt])
		src->args[src->args_cnt] = ft_strdup("");
	if (src->str[src->pos] == '?')
		return (ft_exit_status(src, upstart));
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
	value = ft_get_env_value(key, head);
	if (!value)
		return (!ft_err_parser(NULL, NULL, key, NULL));
	if (ft_err_parser(NULL, NULL, key, NULL) && ft_dissect_value(src, value))
		return (ft_err_parser(NULL, src, NULL, NULL));
	return (0);
}
