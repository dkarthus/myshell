#include "../../includes/minishell.h"

void	ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\b\b  ", 4);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
}
