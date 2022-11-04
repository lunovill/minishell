/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:14:35 by skhali            #+#    #+#             */
/*   Updated: 2022/11/04 17:22:20 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(*word_cmd)->cmds_split = ft_split((*word_cmd)->cmds, '\n');
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

void	pipeline_bis(t_minishell *ms, t_command	**word_cmd,
	t_partition	**pipeline)
{
	*pipeline = malloc(sizeof(t_partition));
	if (!*pipeline)
		return (free(ms->paths), free(ms->cmds), free(ms), exit(1));
	*word_cmd = malloc(sizeof(t_command));
	if (!*word_cmd)
		return (free(*pipeline), free(ms->paths), free(ms->cmds), free(ms),
			exit(1));
}

t_partition	*pipeline_init(t_token *token, t_minishell *ms)
{
	t_partition	*pipeline;
	t_command	*word_cmd;
	t_command	*other_cmds;
	t_token		*first;

	first = token;
	other_cmds = NULL;
	pipeline_bis(ms, &word_cmd, &pipeline);
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
	if (!ms->nb_pipes)
		pipelist = pipeline_init(token, ms);
	while (token && (i <= ms->nb_pipes) && ms->nb_pipes)
	{
		if (i == 0)
			ft_lstadd_front2(&pipelist, pipeline_init(token, ms));
		else
			ft_lstadd_back2(&pipelist, pipeline_init(token, ms));
		token = next_token(token);
		i++;
	}
	ms->partition = pipelist;
	return (ms);
}
