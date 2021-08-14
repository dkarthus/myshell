#include "../../includes/parser.h"
#include "../../includes/minishell.h"

/*
 *	Init func for parser master struct;
 *	@param src parsers master struct that will be initiated;
 *	@param line will de strduped in src struct;
 *	@return 1 = KO ; 0 = OK;
 */
static int	ft_init_src(t_src *src, char *line)
{
	src->str = line;
	src->pos = 0;
	src->args_cnt = 0;
	src->len = (int)ft_strlen(line);
	src->args = ft_calloc(255, sizeof(char *));
	if (!(src->args))
		return (0);
	while (ft_isspace(src->str[src->pos]))
		src->pos++;
	return (1);
}

/*
 * Adds new delimited argument to argument array in src;
 * @param src	parser master struct for passing args array and etc;
 * @return 0 = OK, 1 = KO
 */
static int	ft_add_arg(t_src *src)
{
	int		start;
	int		len;
	char	*arg;
	char	*tmp;

	if (!(src->args[src->args_cnt]))
		src->args[src->args_cnt] = ft_strdup("");
	start = src->pos;
	len = 0;
	while (!ft_check_symbol(src->str[src->pos], 1))
	{
		len++;
		src->pos++;
	}
	arg = ft_substr(src->str, start, len);
	tmp = src->args[src->args_cnt];
	src->args[src->args_cnt] = ft_strjoin(src->args[src->args_cnt], arg);
	if (!(src->args[src->args_cnt]))
		return (ft_err_parser("Malloc error "
				"in parser", src, arg, tmp));
	free (arg);
	free (tmp);
	arg = NULL;
	tmp = NULL;
	return (0);
}

/*
 *	Main parser function, divides incoming str into separate arguments;
 *	@param line	that wii be delimited into args;
 *	@param inst	main struct used for env vars in it;
 *	@param src	sidekick struck for purser ro put its output to;
 *	@return 1 on parser mistake and 0 is OK
 */
int	ft_parse(char *line, t_inst *inst, t_src *src)
{
	int	ret;

	ret = 0;
	if (!(ft_init_src(src, line)))
		return (ft_err_parser("Malloc err in parser", src, NULL, NULL));
	while (src->pos <= src->len && !ret && src->str[src->pos])
	{
		if (line[src->pos] == '\'')
			ret = ft_single_qt(src);
		if (line[src->pos] == '\"' && !ret)
			ret = ft_double_qt(src, inst->env_head);
		if (line[src->pos] == '|' && !ret)
			ret = ft_proc_pipe(src);
		if (line[src->pos] == '$' && !ret)
			ret = ft_dolla(src, inst->env_head, NULL);
		if (line[src->pos] == '>' && !ret)
			ret = ft_redir_out(src);
		if (line[src->pos] == '<' && !ret)
			ret = ft_redir_in(src);
		if (!ft_check_symbol(line[src->pos], 1) && !ret)
			ret = ft_add_arg(src);
		if (!ret)
			skip_wspace(src);
	}
	return (ret);
}
