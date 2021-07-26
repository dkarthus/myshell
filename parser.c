#include "parser.h"

static void ft_init_src(t_src *src, char *line)
{
	src->str = line;
	src->pos = 0;
	src->len = ft_strlen(src);
	src->ref_str = ft_strdup("");
}

int	ft_parse(char *line, t_inst *inst)
{
	t_src	src;
	int 	ret;

	ret = 0;
	ft_init_src(&src, line);
	while(src.pos <= src.len)
	{
		if (line[src.pos] == '\'' && !ret)
			ret = ft_single_qt(&src);
		if (line[src.pos] == '\"' && !ret)
			ret = ft_double_qt(&src, inst);
		if (line[src.pos] == '|' && !ret)
			ret = ft_pipe(&src);
		if (line[src.pos] == '$' && !ret)
			ft_dolla(&src, inst);
		if (line[src.pos] == '>' && !ret)
			ft_redir_out(&src);
		if (line[src.pos] == '<' && !ret)
			ft_redir_in(&src);
		if (ret)
			return (1);
		skip_wspace(&src);
		src.pos++;
	}
}
