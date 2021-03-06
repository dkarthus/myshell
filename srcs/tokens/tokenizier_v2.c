#include "../../includes/parser.h"

/*
 *
 */
static int	ft_set_cmd(t_tkn *tkn, t_src *src, int *arg_iter)
{
	tkn->cmd = ft_strdup(src->args[*arg_iter]);
	tkn->args[0] = ft_strdup(src->args[*arg_iter]);
	if (!tkn->args[0] || !tkn->cmd)
		return (ft_err_parser("Malloc error in parser", src, NULL, NULL));
	(*arg_iter)++;
	return (0);
}

/*
 *
 */
static void	ft_tkn_add_back(t_tkn *tkn, t_tkn **head)
{
	t_tkn	*iter;

	if (!*head)
		*head = tkn;
	else
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = tkn;
	}
}

/*
 *
 */
static int	ft_util_create_tkn(t_tkn *new, t_src *src, int *arg_iter)
{
	if (src->args[*arg_iter] && src->args[*arg_iter][0] == '>')
	{
		if (ft_update_token_fdout(new, src, arg_iter))
			return (1);
	}
	if (src->args[*arg_iter] && src->args[*arg_iter][0] == '<')
	{
		if (ft_update_token_fdin(new, src, arg_iter))
			return (1);
	}
	if (src->args[*arg_iter] && !ft_ch_symbl(src->args[*arg_iter][0]) &&
	new->cmd == NULL)
	{
		if (ft_set_cmd(new, src, arg_iter))
			return (1);
	}
	if (src->args[*arg_iter] && !ft_ch_symbl(src->args[*arg_iter][0]) &&
	new->cmd != NULL)
	{
		if (ft_update_args(new, src, arg_iter))
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
	t_tkn	*new;

	new = ft_init_token(*tkn_cnt);
	if (!new)
		return (1);
	while (src->args[*arg_iter])
	{
		if (ft_util_create_tkn(new, src, arg_iter))
		{
			ft_tkn_add_back(new, head);
			return (1);
		}
		if (src->args[*arg_iter] && src->args[*arg_iter][0] == '|')
		{
			if (ft_is_pipe_tkn(new, src, arg_iter))
			{
				ft_tkn_add_back(new, head);
				return (1);
			}
			break ;
		}
	}
	ft_tkn_add_back(new, head);
	(*tkn_cnt)++;
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
	if (src->args[args_cnt] && src->args[0][0] == '|')
		return (ft_err_parser("Syntax error near '|' token", src, NULL, NULL));
	inst->tkn_head = ft_calloc(sizeof(t_tkn *), 1);
	if (!inst->tkn_head)
		return (ft_err_parser("Malloc error in parser", src, NULL, NULL));
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
