/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_recognition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:57:04 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/01 19:21:27 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tk_operator(t_cmd *cmd)
{
	t_token	*token;
	int		ret;

	ret = 1;
	token = cmd->first;
	while (token && ret)
	{
		if (!ft_strcmp(STRG_LESS, token->s))
			token->id = TK_LESS;
		else if (!ft_strcmp(STRG_GREAT, token->s))
			token->id = TK_GREAT;
		else if (!ft_strcmp(STRG_DLESS, token->s))
			token->id = TK_DLESS;
		else if (!ft_strcmp(STRG_DGREAT, token->s))
			token->id = TK_DGREAT;
		else if (!ft_strcmp(STRG_PIPE, token->s))
			token->id = TK_PIPE;
		if (token->id && ((token->previous && token->previous->id)
					|| !token->next))
		{
			if (token->previous->id != TK_PIPE)
			{
				ret--;
				break ;
			}
		}
		token = token->next;
	}
	if (!ret)
	{
		if (token->previous && token->previous->id)
			ft_printf("minishell: syntax error near unexpected token `%s'\n", token->s);
		else
			ft_printf("minishell: syntax error near unexpected token `newline'\n");
	}
	return (ret);
}

static int	tk_pipe(t_token *current)
{
	while (current) // pipe_sequence
	{
		if (current->id != TK_PIPE)
		{
			while (current->previous && current->previous->id != TK_PIPE)
				current = current->previous;
			tk_command(current); // return ??
		}
		current = current->previous;
	}
	return (1);
}

static void ft_split_cmd(t_cmd *cmd, t_token *current, ssize_t i)
{
	t_token	*token;
	t_token	*new;
	unsigned int j;

	if (i == -1)
		return ;
	token = lst_new();
	token->s = ft_strndup(current->s, i);
	token->id = TK_WD_CMD_NAME;
	lst_add(cmd, current, token);
	while (current->s[i])
	{
		while (current->s[i] && current->s[i] == CHAR_H_TAB
				&& current->s[i] == CHAR_V_TAB
				&& current->s[i] == CHAR_SPACE)
			i++;
		j = i;
		while (current->s[j] && current->s[j] != CHAR_H_TAB
				&& current->s[j] != CHAR_V_TAB
				&& current->s[j] != CHAR_SPACE)
			j++;
		if (current->s[i])
		{
			new = lst_new();
			new->s = ft_strndup(current->s + i, j - i);
			new->id = TK_WORD;
			lst_add(cmd, token, new);
			token = new;
		}
	}
	lst_rmv(cmd, current);
	lst_print(cmd);
	exit(42);
}
static void	tk_split_cmd(t_cmd *cmd)
{
	t_token	*current;

	current = cmd->first;
	while (current)
	{
		if (current->id == TK_WD_CMD_NAME)
		{
			ft_split_cmd(cmd, current, ft_strichr(current->s, CHAR_H_TAB));
			ft_split_cmd(cmd, current, ft_strichr(current->s, CHAR_V_TAB));
			ft_split_cmd(cmd, current, ft_strichr(current->s, CHAR_SPACE));
		}
		current = current->next;
	}
}

t_cmd	*tk_recognition(char *line, char **env)
{
	t_token			*first;
	t_cmd			*cmd;

	first = lst_new();
	if (!first)
		return (NULL);
	cmd = lst_init(first);
	if (!cmd)
		return (ft_free(first), NULL);
	cmd->env = env;
	if (tk_delimiter(line, cmd, first) == -1)
		return (lst_free(cmd), NULL);
	if (!tk_operator(cmd))
		return (lst_free(cmd), NULL);
	if (!tk_pipe(cmd->last))
		return (lst_free(cmd), NULL);
	tk_split_cmd(cmd);
	return (cmd);
}
