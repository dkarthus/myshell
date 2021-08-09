#include "../../includes/minishell.h"

/*
 *
 */
int	ft_fork_cmd(t_inst *inst, t_tkn *tkn)
{
	int	pid;
	int	ret;
	int	pipe_fd[2];
	int save = dup(1);
	pipe(pipe_fd);
	signal(SIGINT, ft_sig_handle_ch);
	if (tkn->is_here_doc && tkn->stop_word)
	{
		if (ft_here_doc(inst, tkn->stop_word, tkn->fd_in))
			return (ft_closefd("Couldn't open fd", pipe_fd, -1));
	}
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (ft_manage_fds(tkn, pipe_fd))
		{
			ft_putstr_fd("manage_fd\n", save);
			exit (1);
		}
		if (command_executor(inst, tkn) != -1)
		{
			ft_putstr_fd("com_eexec\n", save);
			exit (1);
		}
		if (ft_process_bin(inst, tkn))
		{
			ft_putstr_fd("proc_bin\n", save);
			exit(1);
		}
		exit (0);
	}
	waitpid(pid, &ret, 0);
	printf("ret %d\n", ret);
	ft_exit_status_upd(ret);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	return (0);
}

/*
 *
 */
static int	ft_exec_first_tkn(t_inst *inst, t_tkn **tkn)
{
	int	pipe_fd[2];
	int	save;
	printf("ERRRR\n");
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	save = dup(1);
	if ((*tkn)->is_pipe)
	{
		if (pipe(pipe_fd) || dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]))
			return (ft_closefd("FD error", pipe_fd, save));
	}
	if ((*tkn)->fd_out != 1)
	{
		if (dup2((*tkn)->fd_out, 1) == -1)
			return (ft_closefd("Couldn't dup2", pipe_fd, -1));
		close((*tkn)->fd_out);
	}
	else if ((*tkn)->next && (*tkn)->fd_out == 1)
	{
		if (dup2(pipe_fd[1], 1) == -1)
			return (ft_closefd("Couldn't dup2", pipe_fd, -1));
		close(pipe_fd[1]);
	}
	if (command_executor(inst, (*tkn)) == -1)
	{
		close(pipe_fd[1]);
		return (0);
	}
	if ((*tkn)->is_pipe)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
	*tkn = (*tkn)->next;
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	dup2(save, 1);
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
		ft_exec_first_tkn(inst, &tkn);
	while (tkn)
	{
		printf("  %d\n", tkn->id);
		if (ft_fork_cmd(inst, tkn))
			return (1);
		tkn = tkn->next;
	}
	return (0);
}
