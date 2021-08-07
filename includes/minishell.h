#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../includes/parser.h"
# include "../includes/pwd.h"
# include "../includes/cd.h"
# include "../includes/env.h"
# include "../includes/error_exit.h"
# include "../includes/unset.h"
# include "../includes/export.h"
# include "../includes/echo.h"
# include "../includes/exit.h"

int exit_status;

typedef struct s_env t_env;

/*
 * Contains env vars converted into liked-list.
 * Line is one parsed 'line' from *env[],
 * which then divided into 'key' and 'value', next is a pointer to next var elem
 * 'line' parsed from *env[]'
 * 'key' name of the var;
 * 'value' of the var;
 * 'next' pointer to next elem of env vars list;
 */
typedef struct	s_env
{
	char *line;
	char *key;
	char *value;
	t_env *next;
}				t_env;

typedef struct s_token t_tkn;

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
typedef struct	s_token
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

typedef struct	s_instance t_inst;

/*
 * Master struct for minishell, contains all the main data passed through
 * env_vars->parser->tokenizer->executor;
 * 'env_head' head of the linked-list of env vars;
 * 'tkn_head' head of the linked-list of tokens;
 * 'pipes_cnt' amount of pipes in input line;
 * 'fd_in_save' save of 0 stdin fd, used to restor stdin after exec finishes;
 */
typedef struct	s_instance
{
	t_env	**env_head;
	t_tkn	**tkn_head;
	int		pipes_cnt;
	int		fd_in_save;
}				t_inst;

typedef struct	s_u_e t_u_e;

typedef struct	s_u_e
{
	unsigned int	error_check;
	unsigned int	semicolon;
	unsigned int	semicolon_s;
	unsigned int	semicolon_underscore;
	unsigned int	underscore;
	unsigned int	arg;
	unsigned int	equal_sign;
	unsigned int	tilde;
	unsigned int	tilde_slash;
	unsigned int	tilde_slash_s;
	unsigned int	tilde_minus;
	unsigned int	tilde_minus_slash;
	unsigned int	tilde_minus_slash_s;
	unsigned int	tilde_plus;
	unsigned int	tilde_plus_slash;
	unsigned int	tilde_plus_slash_s;
	unsigned int	tilde_1;
	unsigned int	tilde_slash_1;
	unsigned int	tilde_slash_s_1;
	unsigned int	tilde_minus_1;
	unsigned int	tilde_minus_slash_1;
	unsigned int	tilde_minus_slash_s_1;
	unsigned int	tilde_plus_1;
	unsigned int	tilde_plus_slash_1;
	unsigned int	tilde_plus_slash_s_1;
	unsigned int	i;
	unsigned int	comment_symbol;
	unsigned int	failure;
	char			*key;
	char			*value;

}				t_u_e;

//Built-in exec
int		your_wish_is_my_command(t_inst *inst, t_tkn *tkn);
int		ft_here_doc(t_inst *inst, const char *stop_w, int mode);

//Binary exec
int		ft_executor(t_inst *inst);
void	ft_exit_status_upd(int status_ret);
char	*ft_get_bin_path(char *name, t_env **head);
int		ft_closefd(char *err, int *pipe_fd, int fd);

//Env vars utils
char	**ft_group_envs(t_env **head);
int		ft_unset_env_var(char *key, t_env **head);
char	*ft_get_env_value(char *key, t_env **head);
void	ft_free_env(t_env **head);

//Signals
void	ft_sig_handle(int sig);
void	ft_sig_handle_ch(int sig);

#endif
