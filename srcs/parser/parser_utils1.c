#include "../../includes/parser.h"

/*
 *
 */
int	ft_proc_pipe(t_src *src)
{
	if (src->args_cnt == 0 && src->args[src->args_cnt] == NULL)
		return (ft_err_parser("minishell: Syntax error", src, NULL, NULL));
	if (src->str[src->pos + 1] == '|')
		return (ft_err_parser("Sorry, cant interpret ||", src, NULL, NULL));
	if (src->args[src->args_cnt] == 0)
		src->args[src->args_cnt] = ft_strdup("|");
	else
	{
		src->args_cnt++;
		src->args[src->args_cnt] = ft_strdup("|");
	}
	if (!(src->args[src->args_cnt]))
		return (ft_err_parser("Malloc error in parser", src, NULL, NULL));
	src->pos++;
	return (0);
}

/*
 * Parser execs this func when encounters single quotes '
 *
 * @param src parsers struct -> check header parser.h;
 * @return returns 0 on success, and 1 when quotes are not closed;
 */
int	ft_single_qt(t_src *src)
{
	int		start;
	int		len;
	char	*arg;
	char	*tmp;

	len = 0;
	start = ++src->pos;
	while (src->str[src->pos] != '\'')
	{
		if (src->str[src->pos] == 0)
			return (ft_err_parser("Unclosed single quotes", src, NULL, NULL));
		src->pos++;
		len++;
	}
	arg = ft_substr(src->str, start, len - 1);
	if (!(src->args[src->args_cnt]))
		src->args[src->args_cnt] = ft_strdup("");
	tmp = src->args[src->args_cnt];
	src->args[src->args_cnt] = ft_strjoin(src->args[src->args_cnt], arg);
	if (!src->args[src->args_cnt])
		return (ft_err_parser("Malloc error while parsing", src, tmp, arg));
	ft_err_parser(NULL, NULL, tmp, arg);
	src->pos++;
	return (0);
}

/*
 *
 */
int ft_redir_out(t_src *src)
{
	if (src->args[src->args_cnt] == 0)
	{
		if (src->str[src->pos + 1] == '>')
		{
			src->args[src->args_cnt] = ft_strdup(">>");
			src->pos = src->pos + 2;
		}
		else
		{
			src->args[src->args_cnt] = ft_strdup(">");
			src->pos++;
		}
	}
	else
	{
		src->args_cnt++;
		if (src->str[src->pos + 1] == '>')
		{
			src->args[src->args_cnt] = ft_strdup(">>");
			src->pos = src->pos + 2;
		}
		else
		{
			src->args[src->args_cnt] = ft_strdup(">");
			src->pos++;
		}
	}
	return (0);
}

/*
 *
 */
int ft_redir_in(t_src *src)
{
	if (src->args[src->args_cnt] == 0)
	{
		if (src->str[src->pos + 1] == '<')
		{
			src->args[src->args_cnt] = ft_strdup("<<");
			src->pos = src->pos + 2;
		}
		else
		{
			src->args[src->args_cnt] = ft_strdup("<");
			src->pos++;
		}
	}
	else
	{
		src->args_cnt++;
		if (src->str[src->pos + 1] == '<')
		{
			src->args[src->args_cnt] = ft_strdup("<<");
			src->pos = src->pos + 2;
		}
		else
		{
			src->args[src->args_cnt] = ft_strdup("<");
			src->pos++;
		}
	}
	return (0);
}









