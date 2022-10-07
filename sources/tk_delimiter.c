#define CHAR_OPERATOR "<>|"
#define DLESS "<<"
#define DGREAT ">>"
#define NEWLINE 10
#define VTABULATION 11
#define SPACE 32
#define DBL_QUOTE 34
#define EXPANSION 36
#define SGL_QUOTE 39
# include "minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int	tk_isoperator(const char *operator, size_t size)
{
	if (!ft_strncmp(DLESS, operator, size) || !ft_strncmp(DGREAT, operator, size))
		return (0);
	return (-1);
}

ssize_t	ft_quote(const char *line, char quote)
{
	unsigned int	i;

	i = 1;
	while (line[i] != quote)
		if (!line[i++])
			return (-1);
	return (i + 1);
}

unsigned int tk_delimiter(const char *line, unsigned int i, unsigned int j)
{
	while (line[j])
	{
		if (j && ft_strichr(CHAR_OPERATOR, line[j - 1]) != -1)
		{
			if (ft_strichr(CHAR_OPERATOR, line[j]) == -1 || tk_isoperator(line + i, j - i) == -1)
				break ;
			j++;
		}
		else if (line[j] == SGL_QUOTE || line[j] == DBL_QUOTE)
		{
			if (ft_quote(line + j, line[j]) == -1)
				return (exit (42), 0);
			j += ft_quote(line + j, line[j]);
		}
		else if ((j == 0 || ft_strichr(CHAR_OPERATOR, line[j - 1]) == -1) && ft_strichr(CHAR_OPERATOR, line[j]) != -1)
			break ;
		else if (line[j] == NEWLINE || line[j] == VTABULATION || line[j] == SPACE)
			break ;
		else
			j++;
	}
	return (j);
}

t_cmd	*tk_recognition(const char *line)
{
	t_token			*token;
	t_cmd			*cmd;
	unsigned int    i;
	unsigned int    j;

	token = lst_new();
	if (!token)
		return (NULL);
	cmd = lst_init(token);
	if (!cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		j = tk_delimiter(line, i, j);
		token->s = ft_strndup(line + i, j - i);
		if (token != cmd->first)
			lst_add(cmd, cmd->last, token);
		if (line[j] == VTABULATION || line[j] == SPACE)
		{
			while (line[j] && (line[j] == VTABULATION || line[j] == SPACE))
				j++;
			i = j;
		}
		else
		{
			i = j;
			if (line[j])
				j++;
			else
				break ;
		}
		token = lst_new();
	}
	if (i == 0)
		token->s = ft_strdup("");
	return (cmd);
}

int main (void)
{
	char *line;
	t_cmd	*cmd;

//	Les signaux avec signal()
	while((line = readline("minishell> ")))
	{
		add_history(line);
		cmd = tk_recognition(line);
		lst_print(cmd);
	}
	return (0);
}