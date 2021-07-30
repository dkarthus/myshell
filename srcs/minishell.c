#include "../includes/minishell.h"
#include "../includes/parser.h"


int	main(int argc, char *argv[], char *env[])
{
	t_inst	inst;
	t_src src;
	char	*line;
	t_tkn *tmp;
	(void)argv;
	//char	*prompt;

	if (argc != 1)
		return (1);
	inst.env_head = ft_parse_env(env);
	if (!(inst.env_head))
		return (1);
	while (inst.env_head)
	{
		line = readline("<<minishell>>");
		if (!line)
			continue ;
		add_history(line);
		if (ft_parse(line, &inst, &src))
			continue ;
		if (ft_tokenize(&src, &inst))
			continue ;
		tmp = *(inst.tkn_head);
		while (tmp)
		{
			printf("cmd-%s  fd_in-%d  fd_out-%d  is_pipe-%d  is_h_d %d  s_w "
				   "%s\n",
			tmp->cmd, tmp->fd_in, tmp->fd_out, tmp->is_pipe, tmp->is_here_doc, tmp->stop_word);
			printf("arg1 %s\n", tmp->args[0]);
			printf("arg2 %s\n", tmp->args[1]);
			printf("arg3 %s\n", tmp->args[2]);
			tmp = tmp->next;
		}
		free (line);
	}
}

