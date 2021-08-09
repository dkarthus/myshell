#include "../includes/minishell.h"
#include "../includes/export/export.h"
#include "../includes/parser.h"
#include "../includes/cd/cd.h"

/*
 *
 */
static int	ft_update_shell_lvl(t_env **head)
{
	char	*sh_lvl;
	char	tmp[2];
	char	*tmp1;

	sh_lvl = ft_get_env_value("SHLVL", head);
	if (!sh_lvl)
		return (0);
	tmp[0] = *sh_lvl + 1;
	tmp[1] = 0;
	tmp1 = ft_strjoin("SHLVL=", tmp);
	if (!tmp1)
		return (1);
	if (!ft_add_env_elem(tmp1, head))
		return (1);
	free(tmp1);
	return (0);
}

/*
 *
 */
int	main(int argc, char *argv[], char *env[])
{
	t_inst	inst;
	t_src	src;
	char	*line;

	(void)argv;
	if (argc != 1 || !env || !env[0])
		return (1);
	inst.env_head = ft_parse_env(env);
	if (!(inst.env_head) || ft_update_shell_lvl(inst.env_head))
		return (1);
	signal(SIGQUIT, ft_sig_handle);
	g_exit_status = 0;
	inst.fd_in_save = dup(0);
	while (inst.env_head)
	{
		signal(SIGINT, ft_sig_handle);
		line = readline("<<minishell>>");
		if (line == NULL)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		if (*line == 3 || *line == 28)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		int i = 0;
		while (ft_isspace(line[i]))
			i++;
		add_history(line);
		if (ft_parse(&line[i], &inst, &src))
			continue ;
		if (ft_tokenize(&src, &inst))
			continue ;
		ft_executor(&inst);
		free (line);
		dup2(inst.fd_in_save, 0);
	}
}
