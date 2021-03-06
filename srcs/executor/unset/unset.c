#include "../../../includes/minishell.h"

int	if_for_unset(t_u_e *u, int fd_out_save, char *arg)
{
	if (unset_env_name(arg) == 0)
		print_unset_not_a_valid_identifier(fd_out_save, arg);
	else if (unset_env_name(arg) == u->semicolon_underscore)
		return (g_exit_status);
	else if (unset_env_name(arg) == u->tilde)
		unset_tilde(fd_out_save, arg);
	else if (unset_env_name(arg) == u->tilde_slash)
		unset_tilde_slash(fd_out_save, arg);
	else if (unset_env_name(arg) == u->tilde_slash_s)
		unset_tilde_slash_s(fd_out_save, arg);
	return (1);
}

int	if_for_unset_1(t_inst *inst, t_u_e *u, char *arg, char *next_arg)
{
	if (unset_env_name(arg) == u->tilde_minus)
		g_exit_status = unset_tilde_minus(inst, arg);
	else if (unset_env_name(arg) == u->tilde_minus_slash)
		g_exit_status = unset_tilde_minus_slash(inst, arg);
	else if (unset_env_name(arg) == u->tilde_minus_slash_s)
		g_exit_status = unset_tilde_minus_slash_s(inst, arg);
	else if (unset_env_name(arg) == u->tilde_plus)
		g_exit_status = unset_tilde_plus(inst, arg);
	else if (unset_env_name(arg) == u->tilde_plus_slash)
		g_exit_status = unset_tilde_plus_slash(inst, arg);
	else if (unset_env_name(arg) == u->tilde_plus_slash_s)
		g_exit_status = unset_tilde_plus_slash_s(inst, arg);
	else if (unset_env_name(arg) == u->comment_symbol)
		return (g_exit_status);
	else
	{
		u->error_check = ft_unset_env_var(next_arg, inst->env_head);
		if (u->error_check == 0)
		{
			g_exit_status = 1;
			return (g_exit_status);
		}
	}
	return (0);
}

void	initialize_variables_for_unset(t_u_e *u)
{
	u->i = 1;
	g_exit_status = 0;
	u->error_check = 1;
	u->semicolon_underscore = 2;
	u->tilde = 3;
	u->tilde_slash = 4;
	u->tilde_slash_s = 5;
	u->tilde_minus = 6;
	u->tilde_minus_slash = 7;
	u->tilde_minus_slash_s = 8;
	u->tilde_plus = 9;
	u->tilde_plus_slash = 10;
	u->tilde_plus_slash_s = 11;
	u->comment_symbol = 12;
}

int	unset(t_inst *inst, char **args)
{
	t_u_e	u;

	initialize_variables_for_unset(&u);
	if (args[1] != NULL)
	{
		while (args[u.i] != NULL)
		{
			g_exit_status = if_for_unset(&u, inst->fd_out_save, args[u.i]);
			if (g_exit_status == 0)
			{
				u.i++;
				continue ;
			}
			else
				g_exit_status = if_for_unset_1(inst, &u, args[u.i], args[u.i]);
			if (g_exit_status == 0)
			{
				u.i++;
				continue ;
			}
			else
				u.i++;
		}
	}
	return (g_exit_status);
}
