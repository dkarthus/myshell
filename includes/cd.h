#ifndef CD_H
# define CD_H

#include "minishell.h"

typedef struct	s_instance t_inst;
typedef struct	s_token	t_tkn;

int		cd(t_inst *inst, char *arg);
int		your_wish_is_my_command(t_inst *inst, t_tkn *tkn);
int		check_cmd(t_inst *inst, const char *str);
int		check_arg(t_inst *inst, const char *str);
int		substitute_tilde(t_inst *inst, int check);

#endif
