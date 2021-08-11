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
		str_error("chdir() returned -1\n");
	else if (err_code == -2)
		str_error("getcwd() returned NULL\n");
	else if (err_code == -3)
		str_error("ft_add_env_value() returned 0\n");
	else if (err_code == -4)
		str_error("ft_add_env_value(pwd, inst->env_head) returned 0\n");
	else if (err_code == -5)
		str_error("getenv(\"HOME\") returned NULL\n");
	else if (err_code == -6)
		str_error("Malloc has failed\n");
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
void	ft_frees(t_inst *inst, int mode, char *err)
{
	if (mode == 1)
	{
		if (inst->env_head)
			ft_free_env(inst->env_head);
		if (inst->tkn_head)
			ft_free_tkn(inst->tkn_head);
		if (err)
			ft_putstr_fd(err, 1);
		exit (0);
	}
	if (mode == 2)
	{
		if (inst->tkn_head)
			ft_free_tkn(inst->tkn_head);
		if (err)
			ft_putstr_fd(err, 1);
		return ;
	}
}
