/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:56:52 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/05 03:02:08 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*tk_search_expansion(const char *expansion, char **env)
{
	unsigned int	i;
	size_t			size;

	if (!expansion)
		return (NULL);
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
	int		set;

	if (!expansion)
		return (-1);
	set = check_char((*line)[end], 1);
	new = ft_strndup(*line, start);
	if (!set)
		new = (ft_strjoinf(new, "\"", 1));
	if (!new)
		return (-1);
	if (expansion)
		new = ft_strjoinf(new, expansion, 2);
	if (!set)
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
	if (check_char((*line)[end], 1))
		return ((*start)--, tk_add_expansion(&*line, *start, end, NULL), 0);
	else if (ft_isdigit((*line)[end]))
		while (ft_isdigit((*line)[++end]))
			;
	else if ((*line)[end] != '?')
	{
		while ((*line)[end] && !check_char((*line)[end], 0)
			&& !check_char((*line)[end], 1) && !check_char((*line)[end], 2)
			&& !check_char((*line)[end], 3))
			end++;
		if (end == *start)
			return (0);
	}
	else
		end++;
	expansion = ft_strndup(*line + *start, end - *start);
	ret = tk_add_expansion(&*line, --(*start), end,
			tk_search_expansion(expansion, env));
	return (delete_quotes(*line), ret);
}
