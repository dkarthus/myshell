#include "../../includes/minishell.h"

void	ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		write(1, "<<minishell>>", 14);
	}
}

void	ft_sig_handle_ch(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}