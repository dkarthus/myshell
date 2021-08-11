#include "../../includes/minishell.h"

/*
 *
 */
static int	ft_parent(int pid, int *ret, int *pipe_fd)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, ret, 0) == -1)
		return (1);
	ft_exit_status_upd(*ret);
	if (close(pipe_fd[1]) == -1)
		return (1);
	if (dup2(pipe_fd[0], 0) == -1)
		return (1);
	if (close(pipe_fd[0]) == -1)
		return (1);
	return (0);
}

/*
 *
 */
static int	ft_daughter(t_tkn *tkn, t_inst *inst, int *pipe_fd)
{
	signal(SIGQUIT, ft_sig_handle);
	close(pipe_fd[0]);
	if (ft_manage_fds(tkn, pipe_fd))
		exit (1);
	if (command_executor(inst, tkn) != -1)
		exit (1);
	if (ft_process_bin(inst, tkn))
		exit(1);
	exit (0);
}

/*
 *
 */
int	ft_fork_cmd(t_inst *inst, t_tkn *tkn)
{
	int	pid;
	int	ret;
	int	pipe_fd[2];

	pipe(pipe_fd);
	if (tkn->is_here_doc && tkn->stop_word)
	{
		if (ft_here_doc(inst, tkn->stop_word, tkn->fd_in))
			return (ft_closefd("Couldn't open fd", pipe_fd, -1));
	}
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		ft_daughter(tkn, inst, pipe_fd);
	if (ft_parent(pid, &ret, pipe_fd))
		return (1);
	return (0);
}
