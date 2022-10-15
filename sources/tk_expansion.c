#include "minishell.h"
#define CheckQuote(c) (((c) != CHAR_SGL_QUOTE && (c) != CHAR_DBL_QUOTE) ? 0 : (c))


static int tk_add_expansion(char **line, unsigned int start, unsigned int end, const char *expansion, char **env)
{
	char *new;
	unsigned int	i;
	size_t	size;

	i = 0;
	while (env[i])
	{
		size = 0;
		while (env[i][size] && env[i][size] != '=')
			size++;
		if (!ft_strncmp(env[i], expansion, size) && size == ft_strlen(expansion))
		{
			new = ft_strndup(*line, start);
			if (!new)
				return (-1);
			new = ft_strjoinf(new, env[i] + size + 1, 1);
			if (!new)
				return (-1);
			new = ft_strjoinf(new, *line + start + end, 1);
			if (!new)
				return (-1);
			*line = new;
	ft_printf("exp = [%s]", new);
	exit (42);
			return (0);
		}
		i++;
	}
	exit (24);
	return (0);
}

int tk_expansion(char **line, unsigned int *start, char **env)
{
	unsigned int	end;
	char			*expansion;

	end = *start;
	while ((*line)[end] && (*line)[end] != CHAR_EXPANSION
		&&	(*line)[end] != CHAR_H_TAB && (*line)[end] != CHAR_V_TAB && (*line)[end] != CHAR_SPACE
		&&	(*line)[end] != CHAR_DBL_QUOTE && (*line)[end] != CHAR_SGL_QUOTE
		&& ft_strichr(STRG_OPERATOR, (*line)[end] == -1))
		end++;
	if (end == *start)
		return (1);
	else
	{

		expansion = ft_strndup(*line + *start, end - *start);
		if (!expansion)
			return (0);
		(*start)--;
		if (tk_add_expansion(&*line, *start, end, expansion, env) == -1 || !*line)
			return (0);
	}
	return (1);
}