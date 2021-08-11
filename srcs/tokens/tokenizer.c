#include "../../includes/parser.h"

/*
 * Util func ft_create_token for cutting down the size and  adding readability;
 */
static int	ft_fill_util(t_src *src, int *arg_iter, t_tkn *new)
{
	if (src->args[*arg_iter][0] == '>')
	{
		if (ft_update_token_fdout(new, src, arg_iter))
			return (0);
	}
	if (src->args[*arg_iter] && src->args[*arg_iter][0] == '<')
	{
		if (ft_update_token_fdin(new, src, arg_iter))
			return (0);
	}
	if (src->args[*arg_iter] && !ft_ch_symbl(src->args[*arg_iter][0]))
	{
		if (ft_update_args(new, src, arg_iter))
			return (0);
	}
	return (1);
}

/*
 *	Allocates and fills token with cmd from src and tkn_id;
 *	@param	src described in parser.h ;
 *	@param	arg_iter number of current arg from src;
 *	@param	tkn_id number of current token;
 */
static t_tkn	*ft_fill_token(t_src *src, int *arg_iter, int tkn_id)
{
	t_tkn	*new;

	new = ft_init_token(src->args[*arg_iter], tkn_id);
	++(*arg_iter);
	if (!new)
	{
		ft_err_parser("Malloc error", src, NULL, NULL);
		return (0);
	}
	while (src->args[*arg_iter] && src->args[*arg_iter][0] != '|')
	{
		if (!ft_fill_util(src, arg_iter, new))
			return (0);
	}
	if (src->args[*arg_iter] && src->args[*arg_iter][0] == '|')
	{
		if (ft_is_pipe_tkn(new, src, arg_iter))
			return (0);
	}
	return (new);
}

/*
 *	Util func ft_create_token for cutting down the size and  adding readability
 */
int	ft_token_cmd(t_src *src, t_tkn **head, int *arg_iter, int tkn_id)
{
	t_tkn	*iter;

	if (!*head)
	{
		*head = ft_fill_token(src, arg_iter, tkn_id);
		if (!*head)
			return (1);
	}
	else
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = ft_fill_token(src, arg_iter, tkn_id);
		if (!iter->next)
			return (1);
	}
	return (0);
}

/*
 *	Main token crating function, dissects src struct into tokens for our bash
 *	@param	src described in parser.h ;
 *	@param	head of tokens list;
 *	@param	arg_iter number of current arg from src;
 *	@param	tkn_id/tkn_cnt number of current token;
 *	@returns 0 = OK, 1 = KO malloc or fd open error;
 */
int	ft_create_token(t_src *src, t_tkn **head, int *arg_iter, int *tkn_cnt)
{
	if (*tkn_cnt == 0 && src->args[0][0] == '|')
		return (ft_err_parser("\033[90mSyntax error near '|' "
				"token\033[0m", src, NULL, NULL));
	if (src->args[*arg_iter][0] == '>' && *tkn_cnt == 0)
		return (ft_create_blank_file(src, arg_iter));
	if (src->args[*arg_iter][0] == '<' && *tkn_cnt == 0)
		return (ft_blank_check_file(src, arg_iter));
	if (!ft_ch_symbl(src->args[*arg_iter][0]))
	{
		if (ft_token_cmd(src, head, arg_iter, *tkn_cnt))
			return (1);
		(*tkn_cnt)++;
		return (0);
	}
	return (0);
}

/*
 *	Tokenazier is a part that converts parsed and partially digested string in
 *	strict tokens that could in the next step be easily understood by executor;
 *	@param	src described in parser.h ;
 *	@param	inst described in minishell.h ;
 *	@returns 0 = OK, 1 = KO malloc or fd open error;
 */
int	ft_tokenize(t_src *src, t_inst *inst)
{
	int	args_cnt;
	int	tkn_cnt;

	args_cnt = 0;
	tkn_cnt = 0;
	inst->tkn_head = ft_calloc(sizeof(t_tkn *), 1);
	if (!inst->tkn_head)
		return (ft_err_parser("\033[90mMalloc "
				"error in parser\033[0m", src, NULL, NULL));
	while (src->args[args_cnt] && args_cnt <= src->args_cnt)
	{
		if (ft_create_token(src, inst->tkn_head, &args_cnt, &tkn_cnt))
		{
			ft_frees(inst, 2, NULL);
			return (1);
		}
	}
	ft_err_parser(NULL, src, NULL, NULL);
	return (0);
}
