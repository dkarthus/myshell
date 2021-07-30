#include "../includes/parser.h"
#include "../includes/minishell.h"

/*
 *
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
	return (1);
}

/*
 *
 */
static int ft_add_arg(t_src  *src)
{
	int start;
	int len;
	char *arg;
	char *tmp;

	if (!(src->args[src->args_cnt]))
		src->args[src->args_cnt] = ft_strdup("");
	start = src->pos;
	len = 0;
	while(!ft_check_symbol(src->str[src->pos]))
	{
		len++;
		src->pos++;
	}
	arg = ft_substr(src->str, start, len);
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
int	ft_parse(char *line, t_inst *inst, t_src *src)
{
	int 	ret;

	ret = 0;
	if (!(ft_init_src(src, line)))
		return (ft_err_parser("Malloc err in parser", src, NULL, NULL));
	while(src->pos <= src->len && !ret && src->str[src->pos])
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
		if (!ft_check_symbol(line[src->pos]) && !ret)
			ret = ft_add_arg(src);
		skip_wspace(src);
	}

	return (ret);
}
/*

int main(void)
{
	t_inst inst;

	char *src[] = { "b=first", "c=second", "e=frth", "g=fifth", NULL};
	inst.env_head = ft_parse_env(src);
	ft_parse("one\'sdf\' \'dsf\' |two\" th>> >re< <<e $c fo\" sdf$bbur $e<<< "
			 ">>$c", &inst);
}*/
