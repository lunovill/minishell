/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_delimiter_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 02:23:40 by skhali            #+#    #+#             */
/*   Updated: 2022/11/06 16:15:59 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	boucle_p1(t_tmp *tmp, char **line)
{
	(tmp->tab)[0] = check_char((*line)[tmp->j], 0);
	(tmp->tab)[2] = check_char((*line)[tmp->j], 2);
	return ((tmp->tab)[1]);
}

int	boucle_p2(t_tmp *tmp, char **line, t_cmd *cmd)
{
	(tmp->tab)[1] = (*line)[tmp->j];
	if ((tmp->tab)[2])
	{
		tmp->ret = tk_expansion(line, &(tmp->j), cmd->env);
		if (tmp->ret == 1)
			return (42);
		else if (tmp->ret == -1)
			return (free(*line), -1);
	}
	return (0);
}

int	boucle_p3(t_tmp *tmp, char **line, t_cmd *cmd)
{
	(tmp->tab)[2] = 0;
	tmp->ret = tk_expansion(line, &(tmp->j), cmd->env);
	if (tmp->ret == 1)
		return (42);
	else if (tmp->ret == -1)
		return (free(*line), -1);
	return (0);
}

int	boucle_p4_2(t_tmp *tmp, char **line, t_cmd *cmd)
{
	if (((tmp->tab)[1] != CHAR_SGL_QUOTE && (tmp->tab)[2]
	&& !check_char((*line)[tmp->j], 0)) && !(((tmp->tab)[0] && !(tmp->tab)[1]
	&& tk_isoprtr((*line) + (tmp->i), (tmp->j) - (tmp->i))) &&
	((tmp->tab)[0] && !(tmp->tab)[1] && !tk_isoprtr((*line) + tmp->i,
	tmp->j - tmp->i)) && (!(tmp->tab)[1] && check_char((*line)[tmp->j], 1))
	&& ((tmp->tab)[1] && (*line)[tmp->j] == (tmp->tab)[1])))
	{
		tmp->ret = boucle_p3(tmp, line, cmd);
		if (tmp->ret != 0)
			return (tmp->ret);
	}
	return (0);
}

int	boucle_p4(t_tmp *tmp, char **line, t_cmd *cmd)
{
	tmp->ret = boucle_p4_2(tmp, line, cmd);
	if (tmp->ret != 0)
		return (tmp->ret);
	if ((!(tmp->tab)[1] && check_char((*line)[tmp->j], 0)) && !(((tmp->tab)[1]
		!= CHAR_SGL_QUOTE && (tmp->tab)[2]
		&& !check_char((*line)[tmp->j], 0)) && ((tmp->tab)[0] && !(tmp->tab)[1]
		&& tk_isoprtr((*line) + (tmp->i), (tmp->j) - (tmp->i))) &&
		((tmp->tab)[0] && !(tmp->tab)[1] && !tk_isoprtr((*line) + tmp->i,
		tmp->j - tmp->i)) && (!(tmp->tab)[1] && check_char((*line)[tmp->j], 1))
		&& ((tmp->tab)[1] && (*line)[tmp->j] == (tmp->tab)[1])))
		return (-42);
	if ((!(tmp->tab)[1] && check_char((*line)[tmp->j], 3)) && !((!(tmp->tab)[1]
		&& check_char((*line)[tmp->j], 0)) && ((tmp->tab)[1] != CHAR_SGL_QUOTE
		&& (tmp->tab)[2] && !check_char((*line)[tmp->j], 0)) && ((tmp->tab)[0]
		&& !(tmp->tab)[1]
		&& tk_isoprtr((*line) + (tmp->i), (tmp->j) - (tmp->i))) &&
		((tmp->tab)[0] && !(tmp->tab)[1] && !tk_isoprtr((*line) + tmp->i,
		tmp->j - tmp->i)) && (!(tmp->tab)[1] && check_char((*line)[tmp->j], 1))
		&& ((tmp->tab)[1] && (*line)[tmp->j] == (tmp->tab)[1])))
		return (-42);
	return (0);
}
