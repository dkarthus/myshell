#include "../../includes/minishell.h"

void ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
/*		rl_redisplay();
		rl_on_new_line();*/
		write(1, "\n", 1);
		write(1, "<<minishell>>", 14);
	}
}
