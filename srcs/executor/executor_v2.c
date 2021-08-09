#include "../../includes/minishell.h"

/*
 *
 */
static int	ft_manage_fds(t_tkn *tkn, int *pipe_fd)
{
	if (tkn->fd_in > 0)
	{
		if (dup2(tkn->fd_in, 0) == -1)
			return (ft_closefd("Couldn't dup2", pipe_fd, -1));
		close(tkn->fd_in);
	}
	if (tkn->fd_out != 1)
	{
		if (dup2(tkn->fd_out, 1) == -1)
			return (ft_closefd("Couldn't dup2", pipe_fd, -1));
		close(tkn->fd_out);
	}
	else if (tkn->next && tkn->fd_out == 1)
	{
		if (dup2(pipe_fd[1], 1) == -1)
			return (ft_closefd("Couldn't dup2", pipe_fd, -1));
		close(pipe_fd[1]);
	}
	return (0);
}

/*
 *
 */
static int	ft_process_bin(t_inst *inst, t_tkn *tkn)
{
	char	*path;
	char	**arg_env;

	path = ft_get_bin_path(tkn->cmd, inst->env_head);
	arg_env = ft_group_envs(inst->env_head);
	if (!path || !arg_env)
		return (1);
	if (execve(path, tkn->args, arg_env) == -1)
	{
		printf("Couldn't start %s ;", path);
		perror(NULL);
		return (1);
	}
	return (0);
}

/*
 *
 */
void	ft_exit_status_upd(int status_ret)
{
	if (WIFEXITED(status_ret))
	{
		g_exit_status = WEXITSTATUS(status_ret);
		return ;
	}
	if (WIFSIGNALED(status_ret))
	{
		if (WTERMSIG(status_ret) == 2)
			g_exit_status = 130;
		else if (WTERMSIG(status_ret) == 3)
			g_exit_status = 131;
		else
			g_exit_status = 1;
		return ;
	}
	g_exit_status = 0;
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
			return (1);
		if (command_executor(inst, tkn) != -1)
			return (1);
		if (ft_process_bin(inst, tkn))
			return (1);
		return (0);
	}
	waitpid(pid, &ret, 0);
	ft_exit_status_upd(ret);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	return (0);
}
/*

*/
/*
 *
 */

static int	ft_exec_first_tkn(t_inst *inst, t_tkn **tkn)
{
	int	pipe_fd[2];
	int	save;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	save = dup(1);
	if ((*tkn)->is_pipe)
	{
		if (pipe(pipe_fd) || dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]))
		{
			perror("Error: ");
			return (1);
		}
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
static int	ft_find_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", 3))
		return (1);
	if (!ft_strncmp(str, "pwd", 4))
		return (1);
	if (!ft_strncmp(str, "env", 4))
		return (1);
	if (!ft_strncmp(str, "exit", 5))
		return (1);
	if (!ft_strncmp(str, "echo", 5))
		return (1);
	if (!ft_strncmp(str, "unset", 6))
		return (1);
	if (!ft_strncmp(str, "export", 7))
		return (1);
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
	//	printf(" %d %d %s\n", tkn->fd_in, tkn->is_here_doc, tkn->stop_word);
		if (ft_fork_cmd(inst, tkn))
			return (1);
		tkn = tkn->next;
	}
	return (0);
}
