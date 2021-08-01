#include "../../includes/minishell.h"

/*
 *
 */
static int	ft_exec_util(t_tkn *tkn, char *cmd_path)
{

}

/*
 *
 */
int ft_exec_single_cmd(t_inst *inst)
{
	int	pid;
	int ret;
	t_tkn *tkn;
	char *cmd_path;

	tkn = *(inst->tkn_head);
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		cmd_path = ft_find_binary(tkn->cmd, inst->env_head);
		if (!cmd_path)
			return (1);
		return (ft_exec_util(tkn, cmd_path));
	}
	else
	{
		waitpid(pid, &ret, 0);
		if (!WIFEXITED(ret))
			return (WEXITSTATUS(ret));
	}
}

/*
 *
 */
static int **ft_init_pipes(int pipes_cnt)
{
	int	**p_c;
	int	i;

	p_c = ft_calloc(sizeof(int *), pipes_cnt);
	if (!p_c)
		return (0);
	i = 0;
	while (i < pipes_cnt)
	{
		p_c[i] = ft_calloc(sizeof(int), 2);
		if (!p_c[i])
		{
			while(i--)
				free(p_c[i]);
			free(p_c);
			return (0);
		}
		i++;
	}
	return (p_c);
}

/*
 *
 */
int	ft_exec_token(t_inst *inst, t_tkn *tkn)
{
	int **pipe_fd;
	int ret;

	if (inst->pipes_cnt > 0)
	{
		pipe_fd = ft_init_pipes(inst->pipes_cnt);
		if (!pipe_fd)
			return (1);
		return (ft_exec_multi_cmd(inst, pipe_fd));
	}
	else
	{
		if (your_wish_is_my_command(inst,  tkn) == -1)
		return (ft_exec_single_cmd(inst));
	}
}