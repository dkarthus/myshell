#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/cd.h"

/*
 *
 */
//static int ft_update_shell_lvl(t_env **head)
//{
//	char	*sh_lvl;
//	char 	tmp[2];
//	char 	*tmp1;
//
//	sh_lvl = ft_get_env_value("SHLVL", head);
//	tmp[0] = *sh_lvl + 1;
//	tmp[1] = 0;
//	tmp1 = ft_strjoin("SHLVL=", tmp);
//	ft_add_env_elem(tmp1, head);
//	free(tmp1);
//	return (0);
//}

int	main(int argc, char *argv[], char *env[])
{
	t_inst	inst;
	t_src src;
	char	*line;
	t_tkn *tmp;
	(void)argv;

	if (argc != 1 || !env || !env[0])
		return (1);
	inst.env_head = ft_parse_env(env);
//	if (!(inst.env_head) || ft_update_shell_lvl(inst.env_head))
//		return (1);
	signal(SIGQUIT, ft_sig_handle);
	exit_status = 0;
	while (inst.env_head)
	{
		signal(SIGINT, ft_sig_handle);
		inst.fd_in_save = dup(0);
		line = readline("<<minishell>>");
		if (line == NULL)
		{
/*			rl_redisplay();
			rl_on_new_line();*/
			write(1, "exit\n", 6);
			exit(0);
		}
/*		if (!line)
			continue ;*/
		add_history(line);
		if (ft_parse(line, &inst, &src))
			continue ;
		if (ft_tokenize(&src, &inst))
			continue ;
		tmp = *(inst.tkn_head);
		ft_executor(&inst);
//		ft_executor(&inst);
/*		while (tmp)
		{
			printf("cmd-%s  fd_in-%d  fd_out-%d  is_pipe-%d  is_h_d %d  s_w "
				   "%s\n",
			tmp->cmd, tmp->fd_in, tmp->fd_out, tmp->is_pipe, tmp->is_here_doc, tmp->stop_word);
			printf("arg1 %s\n", tmp->args[0]);
			printf("arg2 %s\n", tmp->args[1]);
			printf("arg3 %s\n", tmp->args[2]);
			tmp = tmp->next;
		}
		prompt = ft_get_env_value("PWD", inst.env_head);
		printf("pwd  %s\n", prompt);
		prompt = ft_get_env_value("OLDPWD", inst.env_head);
		printf("oldpwd  %s\n", prompt);*/
		free (line);
		dup2(inst.fd_in_save, 0);
	}
}

