/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:56:22 by lunovill          #+#    #+#             */
/*   Updated: 2022/10/24 21:56:24 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tk_isoprtr(const char *operator, size_t size)
{
	if (!check_char(operator[size], 0))
		return (0);
	if (!ft_strncmp(STRG_DLESS, operator, size + 1)
		|| !ft_strncmp(STRG_DGREAT, operator, size + 1))
		return (1);
	return (0);
}

int	tk_delimiter(char *line, t_cmd *cmd, t_token *token)
{
	int				tab[3];
	int				ret;
	unsigned int	i;
	unsigned int	j;

	tab[0]= 0;
	tab[1] = 0;
	i = 0;
	j = 0;
	while (line[i] && check_char(line[i], 3))
			i++;
	while (line[i])
	{
		if (i && j)
			token = lst_new();
		tab[0]= check_char(line[i], 0);
		tab[1] = check_char(line[i], 1);
		tab[2] = check_char(line[i], 2);
		j = i + 1;
		while (line[j])
		{
			if (tab[0]&& !tab[1] && tk_isoprtr(line + i, j - i))
			{
				tab[0]= check_char(line[j], 0);
				j++;
				continue ;
			}
			else if (tab[0]&& !tab[1] && !tk_isoprtr(line + i, j - i))
				break ;
			else if (!tab[1] && check_char(line[j], 1))
			{
				tab[1] = line[j];
				if (tab[2])
				{
					ret = tk_expansion(&line, &j, cmd->env);
					if (ret == 1)
						continue ;
					else if (ret == -1)
						return (-1);
				}
			}
			else if (tab[1] && line[j] == tab[1])
				tab[1] = 0;
			else if (tab[1] != CHAR_SGL_QUOTE && tab[2] && !check_char(line[j], 0))
			{
				tab[2] = 0;
				ret = tk_expansion(&line, &j, cmd->env);
				if (ret == 1)
					continue ;
				else if (ret == -1)
					return (-1);
			}
			else if (!tab[1] && check_char(line[j], 0))
				break ;
			else if (!tab[1] && check_char(line[j], 3))
				break ;
			tab[0]= check_char(line[j], 0);
			tab[2] = check_char(line[j], 2);
			j++;
		}
		if (tab[1])
			return (ft_putstr_fd("minishell: syntax error token `quote' not closed\n", 2), -1);
		token->s = ft_strndup(line + i, j - i);
		if (token != cmd->first)
			lst_add(cmd, cmd->last, token);
		while (line[j] && check_char(line[j], 3))
			j++;
		i = j;
	}
	if (!j)
		token->s = ft_strdup("");
	return (0);
}
