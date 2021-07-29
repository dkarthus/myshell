#include "../includes/parser.h"

/*
 *
 */
int	ft_create_blank_file(t_src *src, int *arg_iter)
{
	int	i;
	int	fd;

	i = 1;
	if (src->args[*arg_iter][1] == '>')
		i = 2;
	if (src->args[*arg_iter][i] == '\0')
	{
		fd = open(src->args[*arg_iter + 1], O_CREAT);
		if (fd == -1)
			return (ft_err_parser("Can't create file", src, NULL, NULL));
		(*arg_iter)++;
		close(fd);
	}
	else
	{
		fd = open(&src->args[*arg_iter][i], O_CREAT);
		if (fd == -1)
			return (ft_err_parser("Can't create file", src, NULL, NULL));
		close(fd);
	}
	return (0);
}

/*
 *
 */
int	ft_ch_symbl(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
 *
 */
static int ft_get_fd(char *file, int mode)
{
	int fd;

	if (mode == 1)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(file, O_RDWR | O_CREAT |O_APPEND, 0666);
	return (fd);
}

/*
 *
 */
int	ft_update_token_fdout(t_tkn *tkn, t_src *src, int *arg_iter)
{
	int	i;

	i = 1;
	if (tkn->fd_out != 0)
		close(tkn->fd_out);
	if (src->args[*arg_iter][i] == '>')
		i++;
	if (src->args[*arg_iter][i] == '\0')
	{
		(*arg_iter)++;
		if (ft_ch_symbl(src->args[*arg_iter][0]))
			return (ft_err_parser("Parser error near token", src, NULL, NULL));
		tkn->fd_out = ft_get_fd(src->args[*arg_iter], i);
		if (tkn->fd_out == -1)
			return (ft_err_parser("Couldn't access file", src, NULL, NULL));
	}
	else
	{
		if (ft_ch_symbl(src->args[*arg_iter][i]))
			return (ft_err_parser("Parser error near token", src, NULL, NULL));
		tkn->fd_out = ft_get_fd(&src->args[*arg_iter][i], i);
		if (tkn->fd_out == -1)
			return (ft_err_parser("Couldn't access file", src, NULL, NULL));
	}
	return (0);
}

/*
 *
 */
t_tkn *ft_init_token(char *cmd)
{
	t_tkn *new_tkn;

	new_tkn = ft_calloc(sizeof(t_tkn), 1);
	if (!new_tkn)
		return (NULL);
	new_tkn->cmd = ft_strdup(cmd);
	new_tkn->args = ft_calloc(sizeof(char *), 255);
	if (!new_tkn->args || new_tkn->cmd)
		return (NULL);
	new_tkn->next = NULL;
	new_tkn->cmd = NULL;
	new_tkn->fd_in = 0;
	new_tkn->fd_out = 1;
	new_tkn->is_pipe = 0;
	return (new_tkn);
}
