/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:56:22 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/07 17:17:54 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tk_isoprtr(const char *operator, size_t size)
{
	if (!check_char(operator[size], 0))
		return (0);
	if (!ft_strncmp(STRG_DLESS, operator, size + 1)
		|| !ft_strncmp(STRG_DGREAT, operator, size + 1))
		return (1);
	return (0);
}

void	tk_pt1(int *tab, char *line, unsigned int *j)
{
	tab[0] = check_char(line[*j], 0);
	(*j)++;
}

int	tk_boucle(t_tmp *tmp, t_cmd *cmd, char **line)
{
	if ((tmp->tab)[0] && !(tmp->tab)[1] && tk_isoprtr((*line) + (tmp->i),
		(tmp->j) - (tmp->i)))
	{
		tk_pt1(tmp->tab, *line, &(tmp->j));
		return (42);
	}
	else if ((tmp->tab)[0] && !(tmp->tab)[1] && !tk_isoprtr((*line) + tmp->i,
		tmp->j - tmp->i))
		return (-42);
	else if (!(tmp->tab)[1] && check_char((*line)[tmp->j], 1))
	{
		tmp->ret = boucle_p2(tmp, line, cmd);
		if (tmp->ret != 0)
			return (tmp->ret);
	}
	else if ((tmp->tab)[1] && (*line)[tmp->j] == (tmp->tab)[1])
		(tmp->tab)[1] = 0;
	tmp->ret = boucle_p4(tmp, line, cmd);
	if (tmp->ret != 0)
		return (tmp->ret);
	return (boucle_p1(tmp, line));
}

void	free_cmds2(t_cmd *cmds, t_token *tk)
{
	t_token	*token;
	t_token	*tmp;

	if (cmds && cmds->first && cmds->first->s)
	{
		token = cmds->first;
		while (token)
		{
			tmp = token;
			token = token->next;
			if (tmp->s)
				free(tmp->s);
		}
		free(tk);
	}
}

int	tk_delimiter(char *line, t_cmd *cmd, t_token *token, t_tmp *tmp)
{
	tmp->tab = malloc(sizeof(int) * 3);
	tk_pt3(&(tmp->i), (tmp->tab), line, &(tmp->j));
	while (line[(tmp->i)])
	{
		if ((tmp->i) && (tmp->j))
			token = lst_new();
		tk_pt2((tmp->i), (tmp->tab), line, &(tmp->j));
		while (line[(tmp->j)])
		{
			tmp->ret = tk_boucle(tmp, cmd, &line);
			if ((tmp->ret) == -1)
				return (free_cmds2(cmd, token), free(tmp->tab), -1);
			else if ((tmp->ret) == 42)
				continue ;
			else if ((tmp->ret) == -42)
				break ;
			(tmp->j)++;
		}
		if ((tmp->tab)[1])
			return (free_cmds2(cmd, token), free(tmp->tab),
				tk_pt7(), -1);
		token->s = ft_strndup(line + tmp->i, tmp->j - tmp->i);
		(tmp->i) = tk_pt4(cmd, token, &line, &(tmp->j));
	}
	return (tk_pt6(token, (tmp->j)), free(tmp->tab), free(line), 0);
}
