#include "../../includes/minishell.h"

/*
 *
 */
static int ft_manage_fds(t_inst *inst, t_tkn *tkn, int *pipe_fd)
{
	if (tkn->id == 0 && tkn->fd_in == 0)
	{
		if (dup2(inst->fd_in_save, 0) == -1)
			return (ft_closefd("1Couldn't dup2", pipe_fd, -1));
	}
	else if(tkn->fd_in > 0)
	{
		if (dup2(tkn->fd_in, 0) == -1)
			return (ft_closefd("2Couldn't dup2", pipe_fd, -1));
	}
	else if (tkn->is_here_doc && tkn->stop_word)
	{
		if (ft_here_doc(inst, tkn->stop_word, tkn->fd_in))
			return (ft_closefd("3Couldn't open fd", pipe_fd, -1));
	}
	if (tkn->fd_out != 1)
	{
		if (dup2(tkn->fd_out, 1) == -1)
			return (ft_closefd("4Couldn't dup2", pipe_fd, -1));
	}
	else if (tkn->next && tkn->fd_out == 1)
	{
		if (dup2(pipe_fd[1], 1) == -1)
			return (ft_closefd("5Couldn't dup2", pipe_fd, -1));
	}
	return (0);
}

/*
 *
 */
static int ft_process_bin(t_inst *inst, t_tkn *tkn)
{
	char *path;
	char **arg_env;

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
int ft_fork_cmd(t_inst *inst, t_tkn *tkn)
{
	int	pid;
	int ret;
	int pipe_fd[2];

	pipe(pipe_fd);
	if (!(tkn->id % 2) && tkn->next)
		dup2(pipe_fd[0], 0);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (ft_manage_fds(inst, tkn, pipe_fd))
			return (1);
/*		if (your_wish_is_my_command(inst, tkn) != -1)
			return (1);*/
		if (ft_process_bin(inst, tkn))
			return (1);
		return (0);
	}
	waitpid(pid, &ret, 0);
	if (tkn->id % 2 && tkn->next)
		dup2(pipe_fd[0], 0);
/*	close(tkn->fd_in);
	close(tkn->fd_out);*/
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (0);
}

/*
 *
 */
int ft_executor(t_inst *inst)
{
	t_tkn *tkn;
//	int pipe_fd[2];

	tkn = *(inst->tkn_head);
	while (tkn)
	{
/*		pipe(pipe_fd);
		dup2(pipe_fd[0], 0);*/
		if (ft_fork_cmd(inst, tkn))
			return (1);
		tkn = tkn->next;
	//	ft_closefd(NULL, pipe_fd, -1);
	}
	return (0);
}