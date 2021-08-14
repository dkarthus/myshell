#ifndef COMMAND_EXECUTOR_2_H
# define COMMAND_EXECUTOR_2_H

int	execute_unset(t_inst *inst, t_tkn *tkn);
int	execute_export(t_inst *inst, t_tkn *tkn);
int	execute_echo(t_tkn *tkn);
int	execute_exit(int fd_out_save, t_tkn *tkn);
int	execute_is_a_directory(t_inst *inst);

#endif
