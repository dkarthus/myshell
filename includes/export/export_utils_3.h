#ifndef EXPORT_UTILS_3_H
# define EXPORT_UTILS_3_H

unsigned int	export_arg(t_inst *inst, t_u_e *e, char *arg);
void			export_semicolon(t_inst *inst, char *arg);
void			export_semicolon_equal(t_inst *inst, t_u_e *e);
void			print_export_not_a_valid_identifier(int fd_out_save, char *arg);

#endif
