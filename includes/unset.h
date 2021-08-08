#ifndef UNSET_H
# define UNSET_H

int				unset(t_inst *inst, char **args);
unsigned int	unset_env_name(char *str);
void			print_unset_not_a_valid_identifier(char *arg);
void			unset_tilde(char *arg);
void			unset_tilde_slash(char *arg);
void			unset_tilde_slash_s(char *arg);
int				unset_tilde_minus(t_inst *inst, char *arg);
int				unset_tilde_minus_slash(t_inst *inst, char *arg);
int				unset_tilde_minus_slash_s(t_inst *inst, char *arg);
int				unset_tilde_plus(t_inst *inst, char *arg);
int				unset_tilde_plus_slash(t_inst *inst, char *arg);
int				unset_tilde_plus_slash_s(t_inst *inst, char *arg);

#endif
