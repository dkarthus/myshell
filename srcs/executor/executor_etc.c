#include "../../includes/minishell.h"

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
	if (g_exit_status > 255)
	{
		g_exit_status = status_ret / 256;
		return ;
	}
	g_exit_status = 0;
}

/*
 *
 */
int	ft_find_builtin(char *str)
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
int	ft_process_bin(t_inst *inst, t_tkn *tkn)
{
	char	*path;
	char	**arg_env;

	path = ft_get_bin_path(tkn->cmd, inst->env_head);
	arg_env = ft_group_envs(inst->env_head);
	if (!path || !arg_env)
	{
		if (g_exit_status == 127)
			exit (127);
		exit (1);
	}
	if (execve(path, tkn->args, arg_env) == -1)
	{
		printf("Couldn't find bin : %s\n", path);
		exit (1);
	}
	exit (0);
}

/*
 *
 */
int	ft_manage_fds(t_tkn *tkn, int *pipe_fd)
{
	if (tkn->fd_in > 0)
	{
		if (dup2(tkn->fd_in, 0) == -1)
			return (ft_closefd("\033[90mCouldn't dup2\033[0m", pipe_fd, -1));
		close(tkn->fd_in);
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
