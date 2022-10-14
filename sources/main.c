#include "minishell.h"

int main (int ac, char **av, char **env)
{
	char *line;
	t_cmd	*cmd;

//	Les signaux avec signal()
	if (ac == 1)
		av = NULL;
	while((line = readline("minishell> ")))
	{
		add_history(line);
		// ft_printf ("[%s]\n", line);
		cmd = tk_recognition(line, env);
		lst_print(cmd);
	}
	return (0);
}
