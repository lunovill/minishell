/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:17:46 by skhali            #+#    #+#             */
/*   Updated: 2022/11/07 16:48:42 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	is_builtin(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->id == 1)
		{
			if (!ft_strcmp(cmd->cmds_split[0], "echo"))
				return (1);
			else if (!ft_strcmp(cmd->cmds_split[0], "cd"))
				return (1);
			else if (!ft_strcmp(cmd->cmds_split[0], "pwd"))
				return (1);
			else if (!ft_strcmp(cmd->cmds_split[0], "export"))
				return (1);
			else if (!ft_strcmp(cmd->cmds_split[0], "unset"))
				return (1);
			else if (!ft_strcmp(cmd->cmds_split[0], "env"))
				return (1);
			else if (!ft_strcmp(cmd->cmds_split[0], "exit"))
				return (1);
			else
				return (0);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	opening_fd(t_command *token)
{
	if (token->id == 9)
		return (open(token->cmds, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (token->id == 11)
		return (open(token->cmds, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (token->id == 8)
		return (open(token->cmds, O_RDONLY));
	else if (token->id == 10)
		return (open(token->hd->filename, O_RDONLY));
	return (-1);
}

void	redirections_pt2(int *fd_in, int *fd_out)
{
	if (*fd_in > 0)
	{
		dup2(*fd_in, 0);
		close(*fd_in);
	}
	if (*fd_out > 0)
	{
		dup2(*fd_out, 1);
		close(*fd_out);
	}
}

int	redirections(int fd_in, int fd_out, t_command	*cmd)
{
	while (cmd)
	{
		if (cmd->id == 10 || cmd->id == 8)
		{
			if (fd_in > 0)
				close(fd_in);
			fd_in = opening_fd(cmd);
			if (fd_in == -1)
				return (ft_putstr_fd(cmd->cmds, 2),
					ft_putstr_fd(":No such file or directory/permission denied\n"
						, 2), -1);
		}
		else if (cmd->id == 11 || cmd->id == 9)
		{
			if (fd_out > 0)
				close(fd_out);
			fd_out = opening_fd(cmd);
			if (fd_out == -1)
				return (ft_putstr_fd(cmd->cmds, 2),
					ft_putstr_fd(": Is a directory/permission denied\n", 2), -1);
		}
		cmd = cmd->next;
	}
	redirections_pt2(&fd_in, &fd_out);
	return (1);
}

//vérifier si il y a des redirections
//si plusieurs in tous les ouvrir mais recuperer le contenu du dernier
//si plusieurs  out tous les ouvrir mais récuperer le contenu dans le dernier
int	exec_single_builtin(t_minishell *ms)
{
	int			fd[2];
	t_command	*cmd;
	int			fd_in;
	int			fd_out;

	fd_in = -40;
	fd_out = -42;
	cmd = NULL;
	fd[0] = dup(0);
	fd[1] = dup(1);
	cmd = ms->partition->cmds;
	if (redirections(fd_in, fd_out, cmd) == -1)
		return (ft_putstr_fd(": No such file or directory\n", 2), -1);
	cmd = find_word(ms->partition->cmds);
	if (cmd)
		g_status = builtins(fd, ms, cmd->cmds_split, 0);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
	return (0);
}
