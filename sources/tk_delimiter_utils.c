/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_delimiter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 01:07:34 by skhali            #+#    #+#             */
/*   Updated: 2022/11/06 03:48:46 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tk_pt4(t_cmd *cmd, t_token *token, char **line, unsigned int *j)
{
	if (token != cmd->first)
		lst_add(cmd, cmd->last, token);
	while ((*line)[*j] && check_char((*line)[*j], 3))
		(*j)++;
	return (*j);
}

char	*tk_pt5(int *tab, unsigned int i, char *line, unsigned int j)
{
	if (tab[1])
		return (ft_putstr_fd("minishell: syntax error token`quote' not closed\n",
				2), NULL);
	else
		return (ft_strndup(line + i, j - i));
}

int	tk_pt6(t_token *token, unsigned int j)
{
	if (!j)
		token->s = ft_strdup("");
	return (0);
}

void	tk_pt2(unsigned int i, int *tab, char *line, unsigned int *j)
{
	tab[0] = check_char(line[i], 0);
	tab[1] = check_char(line[i], 1);
	tab[2] = check_char(line[i], 2);
	*j = i + 1;
}

void	tk_pt3(unsigned int *i, int *tab, char *line, unsigned int *j)
{
	tab[0] = 0;
	tab[1] = 0;
	*i = 0;
	*j = 0;
	while (line[*i] && check_char(line[*i], 3))
		(*i)++;
}
