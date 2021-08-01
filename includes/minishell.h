#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "parser.h"
# include "cd.h"
# include "env.h"
# include "pwd.h"
# include "error_exit.h"

typedef struct s_env t_env;

typedef struct	s_env
{
	char *line;
	char *key;
	char *value;
	t_env *next;
}				t_env;

typedef struct	s_token t_tkn;

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

typedef struct	s_instance
{
	t_env	**env_head;
	t_tkn	**tkn_head;
	int		pipes_cnt;
	int 	exit_status;
}				t_inst;

//Built-in exec
int		your_wish_is_my_command(t_inst *inst, t_tkn *tkn);

//Binary exec
char	*ft_find_binary(char *name, t_env **head);

//Env vars utils
char	**ft_group_envs(t_env **head);
int		ft_unset_env_var(char *key, t_env **head);
char	*ft_get_env_value(char *key, t_env **head);
void	ft_free_env(t_env **head);

#endif
