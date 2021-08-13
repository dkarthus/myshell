#include "../../includes/minishell.h"

/*
 *
 */
int **ft_init_pipe(t_inst *inst, t_tkn *fst_tkn)
{
	int	i;
	int	**pipe_fd;
	t_tkn *tmp;

	i = 0;
	tmp = fst_tkn;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	inst->pipes_cnt = i - 1;
	pipe_fd = malloc(sizeof(int *) * inst->pipes_cnt);
	i = 0;
	while (pipe_fd && (i < inst->pipes_cnt))
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
			return (NULL);
		pipe(pipe_fd[i]);
		i++;
	}
	return (pipe_fd);
}

/*
 *
 */
static void	ft_thor_odinson(t_inst *inst, t_tkn *tkn, int **pipe_fd)
{
	int i = 0;


	signal(SIGQUIT, ft_sig_handle);
	if (ft_manage_fds(tkn, pipe_fd))
		exit (1);
	while (i < inst->pipes_cnt)
	{
		if(i == tkn->id)
			break ;
		close(pipe_fd[i][1]);
		i++;
	}
	if (command_executor(inst, tkn) != -1)
		exit (1);
	if (ft_process_bin(inst, tkn))
		exit(1);
	exit (0);
}

/*
 *
 */
pid_t ft_exec_tkn(t_inst *inst, t_tkn *tkn, int **pipe_fd)
{
	pid_t	r_u_winning_son;

	if (tkn->is_here_doc && tkn->stop_word)
	{
		if (ft_here_doc(inst, tkn->stop_word, tkn->fd_in))
			return (1);
	}
	r_u_winning_son = fork();
	if (r_u_winning_son < 0)
		return (-1);
	if (!r_u_winning_son)
		ft_thor_odinson(inst, tkn, pipe_fd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (r_u_winning_son);
}

/*
 *
 */
int	ft_exec_multi_tkn(t_inst *inst, t_tkn *tkn, int **pipe_fd)
{
	pid_t	*pids;
	int		ret;
	int		i;

	pids = malloc(sizeof(pid_t) * (inst->pipes_cnt + 1));
	if (!pids)
		return (1);
	while (tkn)
	{
		pids[tkn->id] = ft_exec_tkn(inst, tkn, pipe_fd);
		if (pids[tkn->id] == -1)
			return (1);
		tkn=tkn->next;
	}
	i = 0;
	while(i < inst->pipes_cnt)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		waitpid(pids[i++], &ret, 0);
	}
	waitpid(pids[i], &ret, 0);
	ft_exit_status_upd(ret);
	free(pids);
	return (0);
}
