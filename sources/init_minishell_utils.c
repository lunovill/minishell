/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:21:28 by skhali            #+#    #+#             */
/*   Updated: 2022/11/05 03:11:35 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_parsing(t_token *token)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (token && (token->id != 12))
	{
		if (((token->id == 1) || (token->id == 2) || (token->id == 5
					&& !(token->previous && token->id == 5
						&& token->previous->id == 10))
				|| (token->id == 3)) && (is_notspace(token->s)))
		{
			str = ft_strjoinms(str, token->s);
			str = ft_strjoinms(str, "\n");
			i = 1;
		}
		token = token->next;
	}
	if (i)
		return (str);
	else
		return (free(str), NULL);
}

int	pipe_number(t_cmd *first)
{
	t_token	*cmd;
	int		i;

	cmd = first->first;
	i = 0;
	while (cmd)
	{
		if (cmd->id == 12)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	parsing_paths(t_env *envp, t_minishell *ms)
{
	while (envp && (ft_strncmp("PATH", envp->val, 4)))
		envp = envp->next;
	if (envp)
		ms->paths = ft_split(envp->val, ':');
	else
		ms->paths = NULL;
}

t_token	*next_token(t_token *tk)
{
	while (tk && (tk->id != 12))
		tk = tk->next;
	if (tk)
		return (tk->next);
	else
		return (NULL);
}
