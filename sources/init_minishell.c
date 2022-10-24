/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:14:35 by skhali            #+#    #+#             */
/*   Updated: 2022/10/24 04:37:12 by skhali           ###   ########.fr       */
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
			str = ft_strjoinms(str, " ");
			i = 1;
		}
		token = token->next;
	}
	if (i)
		return (str);
	else
		return (free(str), NULL);
}

t_command	*cmds_parsing(t_token *token)
{
	t_command	*list;

	list = NULL;
	while (token && (token->id != 12))
	{
		if (token->next && ((token->id == 8) || (token->id == 10)
				|| (token->id == 9) || (token->id == 11)))
			ft_lstadd_back3(&list, lst_init_command(token->next->s, token->id));
		token = token->next;
	}
	return (list);
}

t_partition	*pipeline_init(t_token *token)
{
	t_partition	*pipeline;
	t_command	*word_cmd;
	t_command	*other_cmds;
	t_token		*first;

	first = token;
	other_cmds = NULL;
	pipeline = malloc(sizeof(t_partition));
	word_cmd = malloc(sizeof(t_command));
	word_cmd->cmds = word_parsing(token);
	token = first;
	other_cmds = cmds_parsing(token);
	if (word_cmd->cmds)
	{
		word_cmd->id = 1;
		word_cmd->cmds_split = ft_split(word_cmd->cmds, ' ');
		word_cmd->hd = NULL;
		word_cmd->next = other_cmds;
		pipeline->cmds = word_cmd;
		pipeline->next = NULL;
	}
	else if (other_cmds)
	{
		free(word_cmd);
		pipeline->cmds = other_cmds;
		pipeline->next = NULL;
	}
	else
		return (free(pipeline), NULL);
	return (pipeline);
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

t_token *next_token(t_token *tk)
{
	while (tk && (tk->id != 12))
		tk = tk->next;
	if (tk)
		return (tk->next);
	else
		return (NULL);
}

t_minishell *init_minishell(t_minishell *ms, t_cmd *cmd)
{
	t_token		*token;
	t_partition	*pipelist;
	int			i;

	ms->cmds = cmd;
	i = 0;
	ms->nb_pipes = pipe_number(cmd);
	pipelist = NULL;
	parsing_paths(ms->env, ms);
	token = cmd->first;
	if (cmd->last->id == 12)
		return (ft_putstr("erreur de syntax\n"), NULL);
	if (!ms->nb_pipes)
		pipelist = pipeline_init(token);
	while (token && (i <= ms->nb_pipes) && ms->nb_pipes)
	{
		if (i == 0)
			ft_lstadd_front2(&pipelist, pipeline_init(token));
		else
			ft_lstadd_back2(&pipelist, pipeline_init(token));
		token = next_token(token);
		i++;
	}
	ms->partition = pipelist;
	return (ms);
}
