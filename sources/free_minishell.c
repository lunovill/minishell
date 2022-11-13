/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:10:56 by skhali            #+#    #+#             */
/*   Updated: 2022/11/06 04:12:04 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_token	*token;
	t_token	*tmp;

	token = cmds->first;
	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->s)
			free(tmp->s);
		free(tmp);
	}
	free(cmds);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->val);
		free(tmp);
	}
}

void	free_split(char	**str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	free_partitions(t_partition *part)
{
	t_partition	*tmp_part;
	t_command	*cmd;
	t_command	*tmp_cmd;

	while (part)
	{
		cmd = part->cmds;
		while (cmd)
		{
			tmp_cmd = cmd;
			cmd = cmd->next;
			if (tmp_cmd->hd)
			{
				free(tmp_cmd->hd->file);
				free(tmp_cmd->hd->filename);
				free(tmp_cmd->hd);
			}
			free_split(tmp_cmd->cmds_split);
			free(tmp_cmd->cmds);
			free(tmp_cmd);
		}
		tmp_part = part;
		part = part->next;
		free(tmp_part);
	}
}

void	free_minishell(t_minishell *ms)
{
	free_cmds(ms->cmds);
	free_partitions(ms->partition);
	if (ms->paths)
		free_split(ms->paths);
}
