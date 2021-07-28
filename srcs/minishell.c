#include "../includes/minishell.h"


int	main(int argc, char *argv[], char *env[])
{
	t_inst	inst;
	char	*line;
	char	*prompt;

	if (argc != 1)
		return (1);
	inst.env_head = ft_parse_env(env);
	if (!(inst.env_head))
		return (1);
	while (inst.env_head)
	{
		line = readline("<<minishell>>");
		if (!(ft_check_input_line(line)))
			continue ;
		add_history(line);
		if (ft_parse(line, &inst))
			continue ;
		free (line);
	}
}

