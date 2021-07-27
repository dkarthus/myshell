#include "parser.h"

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

	arg = ft_substr(str, *start, *len - 1);
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
 */
static int ft_dissect_value(t_src *src, char *value)
{
	int i;
	int len;
	int start;

	start = 0;
	i = 0;
	while (value[i])
	{
		if (ft_isspace(value[i]))
		{
			if (!(ft_append_arg(src, value, &start, &len)))
				return (1);
			while (ft_isspace(value[i++]));
			start = i;
			len = 0;
		}
		i++;
		len++;
	}
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
int ft_dolla(t_src *src, t_env **head)
{
	int		start;
	int		len;
	char	*key;
	char	*value;

	start = ++src->pos;
	len = 0;
	while (!(ft_check_symbol(src->str[src->pos++])))
		len++;
	key = ft_substr(src->str, start, len - 1);
	if (!(key))
		return (ft_err_parser("Malloc error in parser", src, NULL, NULL));
	value = ft_get_env_value(key, head);
	if (!value)
		return (0);
	if (!src->args[src->args_cnt])
		src->args[src->args_cnt] = ft_strdup("");
	if (ft_dissect_value(src, value))
		return (ft_err_parser(NULL, src, key, value));
	ft_err_parser(NULL, NULL, key, value);
	return (0);
}


/*
static void ft_init_src(t_src *src, char *line)
{
	src->str = line;
	src->pos = 0;
	src->len = ft_strlen(line);
	src->args = ft_strdup("");
}
int main(void)
{
	t_src src;
	char kkk[] = {"'qwert' 'lk"};

	ft_init_src(&src, kkk);
	printf("%s\n", src.str);
	ft_single_qt(&src);
	printf("out %s\n", src.args);
}*/
