#include "minishell.h"

int main (void)
{
	char *line;
	t_cmd	*cmd;

//	Les signaux avec signal()
	while((line = readline("minishell> ")))
	{
		add_history(line);
		// ft_printf ("[%s]\n", line);
		cmd = tk_recognition(line);
		lst_print(cmd);
	}
	return (0);
}
