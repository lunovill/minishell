/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:34:51 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/07 18:11:08 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_split_cmd2(t_cmd *cmd, t_token *current, t_token **token,
unsigned int tab[2])
{
	t_token			*new;

	new = lst_new();
	if (!new)
		return (-1);
	new->s = ft_strndup(current->s + tab[0], tab[1] - tab[0]);
	if (!new->s)
		return (-1);
	if (*token == current)
		new->id = TK_WD_CMD_NAME;
	else
		new->id = TK_WD_CMD_WORD;
	lst_add(cmd, *token, new);
	*token = new;
	return (0);
}

static t_token	*ft_split_cmd(t_cmd *cmd, t_token *current)
{
	t_token			*token;
	unsigned int	tab[2];

	tab[0] = 0;
	token = current;
	while (current->s[tab[0]])
	{
		while (current->s[tab[0]] && check_char(current->s[tab[0]], 3))
			tab[0]++;
		tab[1] = tab[0];
		if (current->s[tab[0]])
			tab[1]++;
		while (current->s[tab[1]] && !check_char(current->s[tab[1]], 3))
			tab[1]++;
		if (current->s[tab[0]])
			if (ft_split_cmd2(cmd, current, &token, tab) == -1)
				return (NULL);
		tab[0] = tab[1];
	}
	ft_free(current->s);
	lst_rmv(cmd, current);
	return (token);
}

int	tk_split_cmd(t_cmd *cmd)
{
	t_token	*current;

	current = cmd->first;
	while (current)
	{
		if (current->id == TK_WD_CMD_NAME
			&& (ft_strichr(current->s, CHAR_H_TAB) != -1
				|| ft_strichr(current->s, CHAR_V_TAB) != -1
				|| ft_strichr(current->s, CHAR_SPACE) != -1))
		{
			current = ft_split_cmd(cmd, current);
			if (!current)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
