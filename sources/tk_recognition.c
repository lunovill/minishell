/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_recognition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:57:04 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/07 17:53:05 by skhali           ###   ########.fr       */
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

static int	tk_operator(t_cmd *cmd, int *ret)
{
	t_token	*token;

	token = cmd->first;
	while (token && *ret)
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
		if (token->id && ((token->previous && token->previous->id
					&& (token->previous->id != TK_PIPE || token->id == TK_PIPE))
				|| !token->next))
		{
			(*ret)--;
			break ;
		}
		token = token->next;
	}
	return (tk_operator_error(token, *ret));
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
	t_tmp			*tmp;
	int				ret;

	ret = 1;
	tmp = malloc(sizeof(t_tmp));
	first = lst_new();
	if (!first)
		return (free(tmp), NULL);
	cmd = lst_init(first);
	if (!cmd)
		return (free(tmp), ft_free(first), NULL);
	cmd->env = env;
	if (tk_delimiter(line, cmd, first, tmp) == -1)
		return (free(tmp), lst_free(cmd), NULL);
	if (!tk_operator(cmd, &ret))
		return (free(tmp), lst_free(cmd), NULL);
	if (!tk_pipe(cmd->last))
		return (free(tmp), lst_free(cmd), NULL);
	if (tk_split_cmd(cmd) == -1)
		return (free(tmp), lst_free(cmd), NULL);
	return (free(tmp), cmd);
}
