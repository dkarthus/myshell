#include "../includes/parser.h"

/*
 *
 *
 */
t_tkn *ft_fill_token(t_src *src, int *arg_iter)
{
	t_tkn *new;

	new = ft_init_token(src->args[*arg_iter]);
	if (!new)
		return (!ft_err_parser("Malloc error in tokenaizer", src, NULL, NULL));
	(*arg_iter)++;
	while (src->args[*arg_iter][0] != '|')
	{
		if (src->args[*arg_iter][0] == '>')
		{
			if (ft_update_token_fdout(new, src, arg_iter))
				return (0);
		}
		else if (src->args[*arg_iter][0] == '<')
		{
			if (ft_update_token_fdin(new, src, arg_iter))
				return (0);
		}
		(*arg_iter)++;
	}
	return (new);
}

/*
 *
 */
int	ft_token_cmd(t_src *src, t_tkn **head, int *arg_iter)
{
	t_tkn *iter;

	if (*head)
	{
		*head = ft_fill_token(src, arg_iter);
		if (!*head)
			return (1);
	}
	else
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = ft_fill_token(src, arg_iter);
		if (!iter->next)
			return (1);
	}
	return (0);
}

/*
 *
 */
int ft_create_token(t_src *src, t_tkn **head, int *arg_iter, int *tkn_cnt)
{

	if (*tkn_cnt == 0 && src->args[0][0] == '|')
		return (ft_err_parser("Syntax error near '|' token", src, NULL, NULL));
	if (src->args[*arg_iter][0] == '>' && *tkn_cnt == 0)
		return (ft_create_blank_file(src, arg_iter));
	if (!ft_ch_symbl(src->args[*arg_iter][0]))
	{
		tkn_cnt++;
		return (ft_token_cmd(src, head, arg_iter));
	}
	return (0);
}

/*
 *
 */
int	ft_tokenize(t_src *src, t_inst *inst)
{
	int args_cnt;
	int tkn_cnt;

	args_cnt = 0;
	tkn_cnt = 0;
	inst->tkn_head = ft_calloc(sizeof(t_tkn *), 1);
	if (!inst->tkn_head)
		return (ft_err_parser("Malloc error in parser", src, NULL, NULL));
	while (src->args[args_cnt] && args_cnt <= src->args_cnt)
	{
		if (ft_create_token(src, inst->tkn_head, &args_cnt, &tkn_cnt))
			return (1);
	}
	return (0);
}
