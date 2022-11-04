/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_recognition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:57:04 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/04 18:06:26 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tk_operator_error(t_token *token, int ret)
{
	if (!ret)
	{
		ft_printf("minishell: syntax error near unexpected ");
		if (token->previous && token->previous->id)
			ft_printf("token `%s'\n", token->s);
		else
			ft_printf("token `newline'\n");
	}
	return (ret);
}

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
				|| !token->next) && token->previous->id != TK_PIPE)
		{
			ret--;
			break ;
		}
		token = token->next;
	}
	return (tk_operator_error(token, ret));
}

static int	tk_pipe(t_token *current)
{
	while (current)
	{
		if (current->id != TK_PIPE)
		{
			while (current->previous && current->previous->id != TK_PIPE)
				current = current->previous;
			tk_command(current);
		}
		current = current->previous;
	}
	return (1);
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
	if (tk_split_cmd(cmd) == -1)
		return (lst_free(cmd), NULL);
	// lst_print(cmd);
	// exit (0);
	return (cmd);
}
