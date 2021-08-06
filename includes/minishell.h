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


int exit_status;
# include "../includes/parser.h"
# include "../includes/pwd.h"
# include "../includes/cd.h"
# include "../includes/env.h"
# include "../includes/error_exit.h"
# include "../includes/unset.h"
# include "../includes/export.h"

typedef struct s_env t_env;

typedef struct	s_env
{
	char *line;
	char *key;
	char *value;
	t_env *next;
}				t_env;

typedef struct s_token t_tkn;

typedef struct	s_token
{
	char	*cmd;
	char	**args;
	int		fd_in;
	int		fd_out;
	int		is_pipe;
	int		is_here_doc;
	int		id;
	char	*stop_word;
	t_tkn	*next;
}				t_tkn;

typedef struct	s_instance t_inst;

typedef struct	s_instance
{
	t_env	**env_head;
	t_tkn	**tkn_head;
	int		pipes_cnt;
	int		fd_in_save;
	int 	exit_status;
}				t_inst;


//Built-in exec
int		your_wish_is_my_command(t_inst *inst, t_tkn *tkn);
int		ft_here_doc(t_inst *inst, const char *stop_w, int mode);

//Binary exec
int		ft_executor(t_inst *inst);
char	*ft_get_bin_path(char *name, t_env **head);
int		ft_closefd(char *err, int *pipe_fd, int fd);
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
	unsigned int	i;
	unsigned int	comment_symbol;
	unsigned int	failure;
	char			*key;
	char			*value;

}				t_u_e;

//Builtin exec
int		your_wish_is_my_command(t_inst *inst, t_tkn *tkn);

//Builtins

//void	cd(t_inst	*inst);


//Env vars utils
char	**ft_group_envs(t_env **head);
int		ft_unset_env_var(char *key, t_env **head);
char	*ft_get_env_value(char *key, t_env **head);
void	ft_free_env(t_env **head);

//Signals
void	ft_sig_handle(int sig);

#endif
