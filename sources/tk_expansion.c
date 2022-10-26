#include "minishell.h"
#define CheckQuote(c) (((c) != CHAR_SGL_QUOTE && (c) != CHAR_DBL_QUOTE) ? 0 : (c))


static int tk_add_expansion(char **line, unsigned int start, unsigned int end, const char *expansion, char **env)
{
	char *new;
	unsigned int	i;
	size_t	size;

	i = 0;

	if (expansion[0] != '?')
	{
		while (env[i])
		{
			size = 0;
			while (env[i][size] && env[i][size] != '=')
				size++;
			if (!ft_strncmp(env[i], expansion, size) && size == ft_strlen(expansion))
				break ;
			i++;
		}
		if (!env[i])
			return (0);
	}
	new = ft_strndup(*line, start);
	if (!new)
		return (-1);
	if (expansion[0] == '?')
		new = ft_strjoinf(new, ft_itoa(g_status), 2);
	else
		new = ft_strjoinf(new, env[i] + size + 1, 1);
	if (!new)
		return (-1);
	new = ft_strjoinf(new, *line + end, 1);
	if (!new)
		return (-1);
	*line = new;
	return (1);
}

int tk_expansion(char **line, unsigned int *start, char **env)
{
	unsigned int	end;
	char			*expansion;
	int				ret;

	end = *start;
	if ((*line)[end] != '?')
	{
		while ((*line)[end] && (*line)[end] != CHAR_EXPANSION
				&&	(*line)[end] != CHAR_H_TAB && (*line)[end] != CHAR_V_TAB && (*line)[end] != CHAR_SPACE
				&&	(*line)[end] != CHAR_DBL_QUOTE && (*line)[end] != CHAR_SGL_QUOTE
				&& ft_strichr(STRG_OPERATOR, (*line)[end] == -1))
			end++;
		if (end == *start)
			return (1);
	}
	else
		end++;
	expansion = ft_strndup(*line + *start, end - *start);
	if (!expansion)
		return (0);
	(*start)--;
	ret = tk_add_expansion(&*line, *start, end, expansion, env);
	if (ret == -1 || !*line)
		return (0);
	else if (ret == 0)
		(*start)++;
	return (1);
}
