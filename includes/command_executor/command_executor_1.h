#ifndef COMMAND_EXECUTOR_1_H
# define COMMAND_EXECUTOR_1_H

int	no_such_file_or_directory_1(int error_check, const char *str);
int	execute_cd(t_inst *inst, t_tkn *tkn);
int	execute_pwd(t_inst *inst);
int	execute_env(t_inst *inst);
int	execute_no_such_file_or_directory_without_cd(t_tkn *tkn);

#endif
