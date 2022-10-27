#include "minishell.h"

int g_status = 0;

int	is_notspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

int main (int argc, char **argv, char **env)
{
	char *line;
	t_cmd	*cmd;
	t_minishell *ms;
	(void)argv;
	(void)argc;
	ms = malloc(sizeof(t_minishell));
	ms->env = create_env(env);
	char ** new_env = envlst_to_tab(ms->env);
	//int i = 0;
	while(1)
	{
		handle_signals();
		g_status = 0;
		line = readline("minishell> ");
		if (!line)
			return (0);
		if (!is_notspace(line))
			continue;
		add_history(line);
		// ft_printf ("[%s]\n", line);
		cmd = tk_recognition(line, new_env);
		if (!cmd)
			return (0);
		ms = init_minishell(ms, cmd);
		if (!ms)
			return (0);
		/*t_partition *ptt = ms->partition;
		t_command *pt;
		while (ptt)
		{
			pt = ptt->cmds;
			while (pt)
			{
				printf("partition : %s, id : %d\n", pt->cmds, pt->id);
				pt = pt->next;
			}
			ptt = ptt->next;
		}*/
		exec(ms);
		//lst_print(cmd);
		free_minishell(ms);
		//printf("%d\n", g_status);
		//i++;
	}
	free_env(ms->env);
	free(ms);
	return (0);
}
