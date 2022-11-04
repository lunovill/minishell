/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:02:51 by skhali            #+#    #+#             */
/*   Updated: 2022/11/04 17:09:29 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_children(t_minishell *ms)
{
	int			status;
	t_partition	*partition;

	status = 0;
	partition = ms->partition;
	while (partition)
	{
		if (!partition->next)
			waitpid(partition->pid, &status, 0);
		else
			waitpid(partition->pid, NULL, 0);
		partition = partition->next;
	}
	handle_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		print_signal(status);
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}

int	close_fds(t_minishell *ms, int *fd, int *tmp)
{
	if (*tmp > 0)
		close(*tmp);
	if ((ms->i != (ms->nb_pipes + 1)) && ms->nb_pipes)
		*tmp = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	exec2(t_minishell *ms)
{
	int			fd[2];
	int			tmp;
	t_partition	*partition;

	partition = ms->partition;
	ms->i = 1;
	tmp = -42;
	reset_signals(ms);
	while (partition)
	{
		if (pipe(fd) == -1)
			return (0);
		partition->pid = fork();
		if (partition->pid == -1)
			return (0);
		if (partition->pid == 0)
			exec_child(ms, partition->cmds, fd, &tmp);
		else
			close_fds(ms, fd, &tmp);
		ms->i = ms->i + 1;
		partition = partition->next;
	}
	return (wait_children(ms));
}

int	exec(t_minishell *ms)
{
	if (!here_doc(ms))
		return (0);
	if (!ms->nb_pipes && is_builtin(ms->partition->cmds))
	{
		if (exec_single_builtin(ms) == -1)
			return (0);
	}
	else
		g_status = exec2(ms);
	return (1);
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
