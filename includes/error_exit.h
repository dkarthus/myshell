#ifndef ERROR_EXIT_H
# define ERROR_EXIT_H

#include "minishell.h"

typedef struct	s_instance t_inst;

void	error_exit(t_inst *inst, int err_code);
//void	init_failed(t_inst *inst, int err_code);

#endif