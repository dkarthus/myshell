#ifndef PWD_H
# define PWD_H

typedef struct s_instance	t_inst;
typedef struct s_token		t_tkn;

int		pwd(t_inst	*inst);
int		check_pwd(t_tkn *tkn);

#endif
