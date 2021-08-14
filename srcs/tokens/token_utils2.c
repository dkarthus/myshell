#include "../../includes/parser.h"

/*
 * Process pipe symbol '|', adds it to a new token;
 * @param	tkn newly created token to add to;
 * @param	src described in parser.h;
 * @param	i src->args count;
 * @returns 0 = OK, 1 = KO malloc error;
 */
int	ft_is_pipe_tkn(t_tkn *tkn, t_src *src, int *arg_iter)
{
	char	*tmp;

	tmp = src->args[*arg_iter];
	if (!tmp)
		return (0);
	if (tmp[1] == '|' || (!tmp[1] && !(tmp + 1)) || ((tmp + 1) && (tmp + 1)
			[0] == '|'))
		return (ft_err_parser("Syntax error", src, NULL, NULL));
	tkn->is_pipe = 1;
	if (tmp[1] != 0)
	{
		src->args[*arg_iter] = ft_strdup(&src->args[*arg_iter][1]);
		free(tmp);
	}
	else
		(*arg_iter)++;
	tmp = NULL;
	return (0);
}

/*
 *	Inits new token and ads cmd as main argument (name of binary);
 *	@param	cmd name of binary that tkn wiil be inited with;
 *	@param	tkn_id number of new tkn;
 *	@returns NULL - KO malloc error, OK - newly inited token pointer;
 */
t_tkn	*ft_init_token(int tkn_id)
{
	t_tkn	*new_tkn;

	new_tkn = ft_calloc(sizeof(t_tkn), 1);
	if (!new_tkn)
		return (NULL);
	new_tkn->cmd = NULL;
	new_tkn->args = ft_calloc(sizeof(char *), 255);
	if (!new_tkn->args)
		return (NULL);
	new_tkn->id = tkn_id;
	new_tkn->next = NULL;
	new_tkn->fd_in = 0;
	new_tkn->fd_out = 1;
	new_tkn->is_pipe = 0;
	new_tkn->is_here_doc = 0;
	new_tkn->stop_word = NULL;
	return (new_tkn);
}

/*
 *	Small util funcs check if char is '|' '<' '>'
 *	@param c char to check
 *	@returns 1 =true, 0 = false
 */
int	ft_ch_symbl(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
