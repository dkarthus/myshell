#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "parser.h"

/*
typedef struct	s_instance
{
	t_env	**env_head;
	int		pipes_cnt;
	t_args **args_head;
}				t_inst;
*/

typedef struct	s_env
{
	char *line;
	char *key;
	char *value;
	t_env *next;
//	t_env *prev;
}				t_env;


//Env vars utils
char	**ft_group_envs(t_env **head);
int		ft_unset_env_var(char *key, t_env **head);
char	*ft_get_env_value(char *key, t_env **head);
void	ft_free_env(t_env **head);



#endif
