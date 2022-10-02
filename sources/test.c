#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main (int ac, char **av, char **env)
{
	char *line;

//	Les signaux avec signal()
	while((line = readline("minishell> ")))
	{
		add_history(line);
		printf("[%s]", line);
	}
	return (0);
}