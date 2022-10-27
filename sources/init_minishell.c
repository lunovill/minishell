/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:14:35 by skhali            #+#    #+#             */
/*   Updated: 2022/10/26 20:09:45 by skhali           ###   ########.fr       */
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

void	pipeline_initp2(t_partition **pipeline, t_command **word_cmd,
	t_command **other_cmds)
{
	int	i;

	i = 0;
	(*word_cmd)->id = 1;
	(*word_cmd)->cmds_split = ft_split((*word_cmd)->cmds, ' ');
	while ((*word_cmd)->cmds_split[i])
	{
		(*word_cmd)->cmds_split[i] = delete_quotes((*word_cmd)->cmds_split[i]);
		i++;
	}
	(*word_cmd)->hd = NULL;
	(*word_cmd)->next = (*other_cmds);
	(*pipeline)->cmds = (*word_cmd);
	(*pipeline)->next = NULL;
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
		pipeline_initp2(&pipeline, &word_cmd, &other_cmds);
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

t_minishell	*init_minishell(t_minishell *ms, t_cmd *cmd)
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
