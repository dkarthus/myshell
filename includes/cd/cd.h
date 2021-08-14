#ifndef CD_H
# define CD_H

# include "../minishell.h"

typedef struct s_instance	t_inst;
typedef struct s_token		t_tkn;

int		cd(t_inst *inst, char *arg);
int		check_arg(t_inst *inst, const char *str);
int		no_such_file_or_directory(int fd_out_save, int error_check, char *str);

#endif
