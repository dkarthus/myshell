#ifndef CD_H
# define CD_H

#include "minishell.h"

typedef struct	s_instance t_inst;
typedef struct	s_token	t_tkn;

int		your_wish_is_my_command(t_inst *inst);
int		check_cmd(t_inst *inst, const char *str);

#endif
