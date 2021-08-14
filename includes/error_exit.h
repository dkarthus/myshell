#ifndef ERROR_EXIT_H
# define ERROR_EXIT_H

# include "minishell.h"

typedef struct s_instance	t_inst;

int	error_exit(int fd_out_save, int err_code);

#endif
