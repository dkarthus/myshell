#ifndef EXPORT_H
#define EXPORT_H

# include "minishell.h"

typedef struct s_env t_env;
typedef struct	s_u_e t_u_e;

int				export(t_inst *inst, char **args);
void			print_export(t_inst *inst);
unsigned int	export_e_v(t_inst *inst, char *str);
void			print_export_not_a_valid_identifier(char *arg);
void			export_tilde(char *arg);
void			export_tilde_slash(char *arg);
void			export_tilde_slash_s(char *arg);
int				export_tilde_minus(t_inst *inst, char *arg);
int				export_tilde_minus_slash(t_inst *inst, char *arg);
int				export_tilde_minus_slash_s(t_inst *inst, char *arg);
int				export_tilde_plus(t_inst *inst, char *arg);
int				export_tilde_plus_slash(t_inst *inst, char *arg);
int				export_tilde_plus_slash_s(t_inst *inst, char *arg);
int				export_comment_symbol(t_inst *inst);
int				export_var(t_inst *inst, t_u_e *e, char *next_arg);

unsigned int	key(t_u_e *e, char *key);
unsigned int	value(t_u_e *e);

#endif
