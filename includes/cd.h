#ifndef CD_H
# define CD_H

#include "minishell.h"

typedef struct	s_instance t_inst;
typedef struct	s_token	t_tkn;

void	cd(t_inst *inst);
int		your_wish_is_my_command(t_inst *inst, t_tkn *tkn);
int		check_cmd(t_inst *inst, const char *str);

#endif
