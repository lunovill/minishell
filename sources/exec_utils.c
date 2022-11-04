/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:32:24 by skhali            #+#    #+#             */
/*   Updated: 2022/11/04 17:05:04 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	cmd_pathp2(char **tmp, char **command, char **paths, char *cmd)
{
	*tmp = ft_strjoin(*paths, "/");
	*command = ft_strjoin(*tmp, cmd);
	free(tmp);
}

char	*cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (!cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
	}
	else
	{
		if (!paths)
			return (NULL);
		while (*paths)
		{
			cmd_pathp2(&tmp, &command, paths, cmd);
			if (access(command, 0) == 0)
				return (command);
			free(command);
			paths++;
		}
	}
	return (NULL);
}

int	env_size(t_env *env)
{
	int		size;
	t_env	*cur;

	size = 0;
	cur = env;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}

char	**envlst_to_tab(t_env *env)
{
	char	**tab;
	int		i;
	t_env	*cur;

	i = 0;
	cur = env;
	tab = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!tab)
		return (NULL);
	while (cur)
	{
		tab[i] = ft_strdup(cur->val);
		cur = cur->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

t_command	*find_word(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->id == 1)
			return (cmd);
		cmd = cmd->next;
	}
	return (NULL);
}
