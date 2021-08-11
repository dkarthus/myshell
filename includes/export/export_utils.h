#ifndef EXPORT_UTILS_H
# define EXPORT_UTILS_H

int		export_comment_symbol(t_inst *inst);
char	*ft_get_env_key(char *key, t_env **head);
int		export_var(t_inst *inst, t_u_e *e, char *next_arg);

#endif
