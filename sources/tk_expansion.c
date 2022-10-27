/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:56:52 by lunovill          #+#    #+#             */
/*   Updated: 2022/10/24 21:56:53 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define CheckQuote(c) (((c) != CHAR_SGL_QUOTE && (c) != CHAR_DBL_QUOTE) ? 0 : (c))

static char	*tk_search_expansion(const char *expansion, char **env)
{
	unsigned int	i;
	size_t			size;

	i = 0;
	if (expansion[0] != '?')
	{
		while (env[i])
		{
			size = 0;
			while (env[i][size] && env[i][size] != '=')
				size++;
			if (!ft_strncmp(env[i], expansion, size)
				&& size == ft_strlen(expansion))
				break ;
			i++;
		}
		if (!env[i])
			return (NULL);
		return (ft_strdup(env[i] + size + 1));
	}
	return (ft_itoa(127));
}

static int	tk_add_expansion(char **line, unsigned int start,
unsigned int end, char *expansion)
{
	char	*new;

	new = ft_strndup(*line, start);
	if (!new)
		return (-1);
	new = (ft_strjoinf(new, "\"", 1));
	if (!new)
		return (-1);
	if (expansion)
	{
		new = ft_strjoinf(new, expansion, 2);
		if (!new)
			return (-1);
	}
	new = (ft_strjoinf(new, "\"", 1));
	if (!new)
		return (-1);
	new = ft_strjoinf(new, *line + end, 1);
	if (!new)
		return (-1);
	*line = new;
	return (1);
}

int	tk_expansion(char **line, unsigned int *start, char **env)
{
	unsigned int	end;
	char			*expansion;
	int				ret;

	end = *start;
	if ((*line)[end] != '?')
	{
		while ((*line)[end] && (*line)[end] != CHAR_EXPANSION
				&& (*line)[end] != CHAR_H_TAB
				&& (*line)[end] != CHAR_V_TAB
				&& (*line)[end] != CHAR_SPACE
				&& (*line)[end] != CHAR_DBL_QUOTE
				&& (*line)[end] != CHAR_SGL_QUOTE
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
	ret = tk_add_expansion(&*line, *start, end,
			tk_search_expansion(expansion, env));
	if (ret == -1 || !*line)
		return (0);
	ft_printf("[%c]\n\n", (*line)[*start]);
	return (1);
}
