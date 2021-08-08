#ifndef EXPORT_H
#define EXPORT_H

typedef struct s_env t_env;
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

int				export(t_inst *inst, char **args);

#endif
