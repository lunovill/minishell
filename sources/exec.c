/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:56:18 by skhali            #+#    #+#             */
/*   Updated: 2022/11/04 16:50:10 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	exec_cmd(t_minishell *ms, t_command *cmds)
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
			return (g_status = builtins(ms, cmds->cmds_split, 1), 1);
		else
		{
			path = cmd_path(ms->paths, cmds->cmds_split[0]);
			if (!path)
				return (write(2, cmds->cmds_split[0],
						ft_strlen(cmds->cmds_split[0])),
					write(2, ": command not found\n", 20), g_status = 127, 1);
			if (execve(path, cmds->cmds_split, envlst_to_tab(ms->env)) == -1)
				return (write(2, "execve error\n", 13), g_status = 1, 1);
		}
	}
	return (1);
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
		ft_putstr_fd(": No such file or directory\n", 2);
		g_status = 1;
		close(fd2[1]);
		close(fd2[0]);
		free_minishell(ms);
		if (ms->char_env)
			free_split(ms->char_env);
		free(ms);
		exit(1);
	}
	exec_cmd(ms, cmd);
	dup2(fd2[0], 0);
	dup2(fd2[1], 1);
	close(fd2[1]);
	close(fd2[0]);
	free_minishell(ms);
	if (ms->char_env)
		free_split(ms->char_env);
	free_env(ms->env);
	free(ms);
	exit(127);
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

void	print_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (signal - 128 == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
