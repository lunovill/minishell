/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:56:18 by skhali            #+#    #+#             */
/*   Updated: 2022/11/07 16:59:47 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_minishell *ms, t_command *cmds, int *fd)
{
	char		*path;
	t_command	*cmd;

	cmd = find_word(cmds);
	if (!cmd)
		return (1);
	else
	{
		handle_signals();
		if (is_builtin(cmds))
			return (g_status = builtins(fd, ms, cmds->cmds_split, 1), 1);
		else
		{
			if ((!ft_strcmp(cmds->cmds_split[0], ".."))
				|| (!ft_strcmp(cmds->cmds_split[0], ".")))
				return (command_notfound(cmds), g_status = 127, 1);
			path = cmd_path(ms->paths, cmds->cmds_split[0]);
			if (!path)
				return (command_notfound(cmds), g_status = 127, 1);
			if (execve(path, cmds->cmds_split, ms->char_env) == -1)
				return (command_notfound(cmds), g_status = 126, 1);
		}
	}
	return (1);
}

void	exec_child_utils_free(t_minishell *ms)
{
	free_minishell(ms);
	free_env(ms->env);
	if (ms->char_env)
		free_split(ms->char_env);
	free(ms);
}

void	exec_child_utils(t_minishell *ms, t_command *cmd)
{
	int	fd_in;
	int	fd_out;
	int	fd2[2];

	fd_in = -40;
	fd_out = -42;
	fd2[0] = dup(0);
	fd2[1] = dup(1);
	if (redirections(fd_in, fd_out, cmd) == -1)
	{
		g_status = 1;
		close(fd2[1]);
		close(fd2[0]);
		exec_child_utils_free(ms);
		exit(1);
	}
	exec_cmd(ms, cmd, fd2);
	dup2(fd2[0], 0);
	dup2(fd2[1], 1);
	close(fd2[1]);
	close(fd2[0]);
	exec_child_utils_free(ms);
	exit(g_status);
}

void	exec_between(t_minishell *ms, t_command *cmd, int *fd, int *tmp)
{
	close(fd[0]);
	dup2(*tmp, STDIN_FILENO);
	close(*tmp);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_child_utils(ms, cmd);
}

void	exec_child(t_minishell *ms, t_command *cmd, int *fd, int *tmp)
{
	if (!ms->nb_pipes)
	{
		close(fd[0]);
		close(fd[1]);
		exec_child_utils(ms, cmd);
	}
	else if (ms->i == 1 && ms->nb_pipes)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_child_utils(ms, cmd);
	}
	else if (ms->i == (ms->nb_pipes + 1))
	{
		dup2(*tmp, STDIN_FILENO);
		close(*tmp);
		exec_child_utils(ms, cmd);
	}
	else
		exec_between(ms, cmd, fd, tmp);
}
