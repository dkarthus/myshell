#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "history.h"
# include "readline.h"
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../includes/parser.h"
# include "../includes/pwd.h"
# include "../includes/cd/cd.h"
# include "../includes/env.h"
# include "../includes/error_exit.h"
# include "../includes/unset.h"
# include "../includes/echo.h"
# include "../includes/exit.h"
# include "cd/update_old_pwd.h"
# include "cd/update.h"
# include "cd/cd_else.h"
# include "cd/check_tilde_plus_minus_path.h"
# include "cd/update_pwd.h"
# include "export/export.h"
# include "export/if_for_export.h"
# include "export/export_utils.h"
# include "export/export_utils_1.h"
# include "export/export_utils_2.h"
# include "export/export_utils_3.h"
# include "export/print_export.h"
# include "export/print_export_1.h"
# include "command_executor/command_executor.h"
# include "command_executor/command_executor_1.h"
# include "command_executor/command_executor_2.h"

int							g_exit_status;

typedef struct s_env		t_env;

/*
 * Contains env vars converted into liked-list.
 * Line is one parsed 'line' from *env[],
 * which then divided into 'key' and 'value', next is a pointer to next var elem
 * 'line' parsed from *env[]'
 * 'key' name of the var;
 * 'value' of the var;
 * 'next' pointer to next elem of env vars list;
 */
typedef struct s_env
{
	char		*line;
	char		*key;
	char		*value;
	t_env		*next;
}				t_env;

typedef struct s_token		t_tkn;

/*
 * Token is a structured data for executor to process.
 *  'cmd' is a built-in or binary name;
 *  'args' are arguments for the command;
 *  'fd_in' input file descriptor;
 *  'fd_out' output file descriptor;
 *  'is_pipe' flag for pipe and there for existence of next token;
 *  'is_here_doc' flag for here_doc util;
 *  'stop_word' is stop word for here_doc;
 *  'id' is number of current token;
 *  'next' pointer to next elem of the token list;
 */
typedef struct s_token
{
	char	*cmd;
	char	**args;
	int		fd_in;
	int		fd_out;
	int		is_pipe;
	int		is_here_doc;
	char	*stop_word;
	int		id;
	t_tkn	*next;
}				t_tkn;

typedef struct s_instance	t_inst;

/*
 * Master struct for minishell, contains all the main data passed through
 * env_vars->parser->tokenizer->executor;
 * 'env_head' head of the linked-list of env vars;
 * 'tkn_head' head of the linked-list of tokens;
 * 'pipes_cnt' amount of pipes in input line;
 * 'fd_in_save' save of 0 stdin fd, used to restor stdin after exec finishes;
 */
typedef struct s_instance
{
	t_env	**env_head;
	t_tkn	**tkn_head;
	int		pipes_cnt;
	int		fd_in_save;
	int		fd_out_save;
}				t_inst;
typedef struct s_source		t_src;

//Built-in exec
int		ft_here_doc(t_inst *inst, const char *stop_w, int mode);
int		ft_find_builtin(char *str);

//Binary exec
int		ft_executor(t_inst *inst);
void	ft_exit_status_upd(int status_ret);
char	*ft_get_bin_path(char *name, t_inst *inst);
int		ft_process_bin(t_inst *inst, t_tkn *tkn);
int		ft_manage_fds(t_tkn *tkn, int **pipe_fd);
int		ft_closefd(char *err, int *pipe_fd, int fd);
int		ft_first_token(t_inst *inst, t_tkn **tkn);

//Env vars utils
char	**ft_group_envs(t_env **head);
int		ft_unset_env_var(char *key, t_env **head);
char	*ft_get_env_value(char *key, t_env **head);

//Signals
void	ft_sig_handle(int sig);
void	ft_sig_handle_ch(int sig);

//Free&Exit
int		ft_frees(t_inst *inst, int mode, char *err);
int		ft_fr_pipe(int **pipe_fd, int pipe_cnt);
void	ft_free_env(t_env **head);
void	ft_free_tkn(t_tkn **head);

#endif
