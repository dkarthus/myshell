#include "../../includes/minishell.h"

/*
 *
 */
static int	ft_manage_fds_fst_tkn(t_tkn *tkn, int *pipe_fd)
{
	if (tkn->is_pipe)
	{
		if (pipe(pipe_fd))
			return (ft_closefd("\033[90mFD error\033[0m", pipe_fd, -1));
	}
	if (tkn->fd_out != 1)
	{
		if (dup2(tkn->fd_out, 1) == -1)
			return (ft_closefd("\033[90mCouldn't dup2\033[0m", pipe_fd, -1));
		close(tkn->fd_out);
	}
	else if (tkn->next && tkn->fd_out == 1)
	{
		if (dup2(pipe_fd[1], 1) == -1)
			return (ft_closefd("\033[90mCouldn't dup2\033[0m", pipe_fd, -1));
		close(pipe_fd[1]);
	}
	return (0);
}

/*
 *
 */
static void	ft_print_err(void)
{
	char	buf[4096];
	int		bytes;

	ft_memset(buf, 0, 4096);
	bytes = read(0, buf, 4096);
	ft_putstr_fd(buf, 1);
}

/*
 *
 */
static int	ft_exec_fst_util(t_tkn *tkn, int ret, int *pipe_fd, int save)
{
	if (ret == -1)
	{
		if (close(pipe_fd[0]) == -1 || dup2(save, 1) == -1)
			return (1);
		return (0);
	}
	if (tkn->is_pipe)
	{
		if (dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]) == -1)
			return (1);
	}
	if (dup2(save, 1) == -1)
		return (1);
	if (ret == 1 && tkn->is_pipe)
		ft_print_err();
	return (0);
}

/*
 *
 */
static int	ft_exec_first_tkn(t_inst *inst, t_tkn **tkn)
{
	int	pipe_fd[2];
	int	save;
	int	ret;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	save = dup(1);
	if (ft_manage_fds_fst_tkn(*tkn, pipe_fd))
		return (1);
	ret = command_executor(inst, (*tkn));
	if (ft_exec_fst_util(*tkn, ret, pipe_fd, save))
		return (1);
	*tkn = (*tkn)->next;
	return (0);
}

/*
 *
 */
int	ft_executor(t_inst *inst)
{
	t_tkn	*tkn;

	tkn = *(inst->tkn_head);
	if (tkn && ft_find_builtin(tkn->cmd))
	{
		if (ft_exec_first_tkn(inst, &tkn))
		{
			ft_frees(inst, 2, NULL);
			return (1);
		}
	}
	while (tkn)
	{
		if (ft_fork_cmd(inst, tkn))
		{
			ft_frees(inst, 2, NULL);
			return (1);
		}
		tkn = tkn->next;
	}
	ft_frees(inst, 2, NULL);
	return (0);
}
