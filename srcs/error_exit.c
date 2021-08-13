#include "../includes/minishell.h"

void	str_error(const char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	g_exit_status = 1;
}

int	error_exit(int err_code)
{
	write(1, "\033[31mError\033[0m\n", 15);
	if (err_code == -1)
		str_error("\033[90mchdir() returned -1\033[0m\n");
	else if (err_code == -2)
		str_error("\033[90mgetcwd() returned NULL\033[0m\n");
	else if (err_code == -3)
		str_error("\033[90mft_add_env_value() returned 0\033[0m\n");
	else if (err_code == -4)
		str_error("\033[90mft_add_env_value(pwd, inst->env_head) "
			  "returned 0\033[0m\n");
	else if (err_code == -5)
		str_error("\033[90mgetenv(\"HOME\") returned NULL\033[0m\n");
	else if (err_code == -6)
		str_error("\033[90mMalloc has failed\033[0m\n");
	return (g_exit_status);
}

/*
 *
 */
static void	ft_free_tkn(t_tkn **head)
{
	t_tkn	*tmp;
	t_tkn	*tmp1;
	int		i;

	tmp = *head;
	while (tmp)
	{
		free(tmp->cmd);
		free(tmp->stop_word);
		tmp->cmd = NULL;
		tmp->stop_word = NULL;
		i = 0;
		while (tmp->args[i])
			free((tmp->args[i++]));
		free(tmp->args);
		tmp->args = NULL;
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
		tmp1 = NULL;
	}
	free(head);
	head = NULL;
}

/*
 *
 */
int	ft_frees(t_inst *inst, int mode, char *err)
{
	if (mode == 1)
	{
		if (inst->env_head)
			ft_free_env(inst->env_head);
		if (inst->tkn_head)
			ft_free_tkn(inst->tkn_head);
		if (err)
			ft_putstr_fd(err, 1);
	}
	if (mode == 2)
	{
		if (err)
			ft_putstr_fd(err, 1);
		if (inst->tkn_head)
			ft_free_tkn(inst->tkn_head);
		return (1) ;
	}
	if (mode == 3)
	{
		if (inst->env_head)
			ft_free_env(inst->env_head);
		if (err)
			ft_putstr_fd(err, 1);
	}
	exit (0);
}
