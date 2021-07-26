#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*
 * Struct for parser module
 *
 * @param str input str form readline;
 * @param len length of str;
 * @param pos read position;
 * @param refactored string;
 */
typedef struct	s_source
{
	char	*str;
	int 	len;
	int		pos;
	char	*ref_str;
}				t_src;

int		ft_parse(char *line, t_inst *inst);

//Env vars parser
t_env	**ft_parse_env(char *env[]);
int		ft_add_env_elem(char *src, t_env **head);

//Utils
int		ft_check_input_line(char *line);
void	skip_wspace(t_src *src);
int		ft_single_qt(t_src *src);

//Error handler
int		ft_err_parser(const char *str, t_src *src, char *to_free1, char *to_free2);

#endif
