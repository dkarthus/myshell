#include "../../includes/minishell.h"

void	ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
//		write(1, "<<minishell>>", 14);
		rl_replace_line("\0", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}

void	ft_sig_handle_ch(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGQUIT)
		exit (0);
}
