#include "../includes/parser.h"

 /*
  *
  */
 int ft_update_args(t_tkn *tkn, t_src *src, int *arg_iter)
 {
 	int	i;

 	if (!tkn->args)
	{
 		tkn->args = ft_calloc(sizeof(char *), 255);
 		if (!tkn->args)
			return (ft_err_parser("Malloc error in parser", src, NULL, NULL));
	}
 	i = 0;
 	while (tkn->args[i])
 		i++;
 	tkn->args[i] = ft_strdup(src->args[*arg_iter]);
 	if (!tkn->args[i])
 		return (ft_err_parser("Malloc error in parser", src, NULL, NULL));
 	(*arg_iter)++;
 	return (0);
 }

 /*
  *
  */
 static int ft_get_fd(char *str, int mode, t_tkn *tkn)
 {
 	int fd;

 	if (mode == 1)
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
			return (ft_err_parser("Couldn't access file", NULL, NULL, NULL));
	}
 	else
	{
 		fd = -1;
 		tkn->is_here_doc = 1;
 		tkn->stop_word = ft_strdup(str);
 		if (!tkn->stop_word)
			return (ft_err_parser("Malloc err in parser", NULL, NULL, NULL));
	}
	 return (fd);
 }

 /*
  *
  */
int	ft_update_token_fdin(t_tkn *tkn, t_src *src, int *arg_iter)
{
	int	i;

	i = 1;
	if (tkn->fd_in != 0)
		close(tkn->fd_in);
	if (src->args[*arg_iter][i] == '>')
		i++;
	if (src->args[*arg_iter][i] == '\0')
	{
		(*arg_iter)++;
		if (ft_ch_symbl(src->args[*arg_iter][0]))
			return (ft_err_parser("Parser error near token", src, NULL, NULL));
		tkn->fd_in = ft_get_fd(src->args[*arg_iter], i, tkn);
		if (tkn->fd_in == 1)
			return (ft_err_parser(NULL, src, NULL, NULL));
	}
	else
	{
		if (ft_ch_symbl(src->args[*arg_iter][i]))
			return (ft_err_parser("Parser error near token", src, NULL, NULL));
		tkn->fd_in = ft_get_fd(&src->args[*arg_iter][i], i, tkn);
		if (tkn->fd_in == 1)
			return (ft_err_parser(NULL, src, NULL, NULL));
	}
	(*arg_iter)++;
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
	if (!new_tkn->args || !new_tkn->cmd)
		return (NULL);
	new_tkn->next = NULL;
	new_tkn->fd_in = 0;
	new_tkn->fd_out = 1;
	new_tkn->is_pipe = 0;
	new_tkn->is_here_doc = 0;
	new_tkn->stop_word = NULL;
	return (new_tkn);
}

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
		(*arg_iter)++;
		if (!src->args[*arg_iter] || ft_ch_symbl(src->args[*arg_iter][0]))
			return (ft_err_parser("Syntax error", src, NULL, NULL));
		fd = open(src->args[*arg_iter + 1], O_CREAT);
		if (fd == -1)
			return (ft_err_parser("Can't create file", src, NULL, NULL));
		close(fd);
	}
	else
	{
		fd = open(&src->args[*arg_iter][i], O_CREAT);
		if (fd == -1)
			return (ft_err_parser("Can't create file", src, NULL, NULL));
		close(fd);
	}
	(*arg_iter)++;
	return (0);
}