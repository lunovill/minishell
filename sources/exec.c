/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:56:18 by skhali            #+#    #+#             */
/*   Updated: 2022/10/23 15:27:38 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	exec_cmd(t_minishell *ms, t_command *cmds)
{
	char		*path;
	t_command	*cmd;
	int			status;
	int			i;

	status = 0;
	i = 0;
	cmd = find_word(cmds);
	if (!cmd)
		return (1);
	else
	{
		handle_signals();
		if (is_builtin(cmds))
			return (status = builtins(ms, cmds->cmds_split, 1),
				exit(status), 1);
		else
		{
			path = cmd_path(ms->paths, cmds->cmds_split[0]);
			if (!path)
				return (write(2, cmds->cmds_split[0],
						ft_strlen(cmds->cmds_split[0])),
					write(2, ": command not found\n", 20), g_status = 127, 1);
			if (execve(path, cmds->cmds_split, envlst_to_tab(ms->env)) == -1)
				return (write(2, cmds->cmds_split[0],
						ft_strlen(cmds->cmds_split[0])),
					write(2, ": command not found\n", 20), g_status = 127, 1);
			if (!WIFEXITED(status))
			{
				printf("test\n");
				i = WEXITSTATUS(status);
				exit(i);
			}
		}
	}
	return (1);
}

void	exec_child(t_minishell *ms, t_command *cmd, int *fd, int i, int *tmp)
{
	int	fd_in;
	int	fd_out;
	int	fd2[2];

	fd_in = -40;
	fd_out = -42;
	if (!ms->nb_pipes)
	{
		close(fd[0]);
		close(fd[1]);
		fd2[0] = dup(0);
		fd2[1] = dup(1);
		redirections(fd_in, fd_out, cmd);
		exec_cmd(ms, cmd);
		dup2(fd2[0], 0);
		dup2(fd2[1], 1);
		close(fd2[1]);
		close(fd2[0]);
		free_minishell(ms);
		free_env(ms->env);
		free(ms);
		exit(127);
	}
	else if (i == 1 && ms->nb_pipes)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		fd2[0] = dup(0);
		fd2[1] = dup(1);
		redirections(fd_in, fd_out, cmd);
		exec_cmd(ms, cmd);
		dup2(fd2[0], 0);
		dup2(fd2[1], 1);
		close(fd2[1]);
		close(fd2[0]);
		free_minishell(ms);
		free_env(ms->env);
		free(ms);
		exit(127);
	}
	else if (i == (ms->nb_pipes + 1))
	{
		dup2(*tmp, STDIN_FILENO);
		close(*tmp);
		fd2[0] = dup(0);
		fd2[1] = dup(1);
		redirections(fd_in, fd_out, cmd);
		exec_cmd(ms, cmd);
		dup2(fd2[0], 0);
		dup2(fd2[1], 1);
		close(fd2[1]);
		close(fd2[0]);
		free_minishell(ms);
		free_env(ms->env);
		free(ms);
		exit(127);
	}
	else
	{
		close(fd[0]);
		dup2(*tmp, STDIN_FILENO);
		close(*tmp);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		fd2[0] = dup(0);
		fd2[1] = dup(1);
		redirections(fd_in, fd_out, cmd);
		exec_cmd(ms, cmd);
		dup2(fd2[0], 0);
		dup2(fd2[1], 1);
		close(fd2[1]);
		close(fd2[0]);
		free_minishell(ms);
		free_env(ms->env);
		free(ms);
		exit(127);
	}
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

int	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	exec2(t_minishell *ms)
{
	int			fd[2];
	int			tmp;
	int			i;
	t_partition	*partition;

	partition = ms->partition;
	i = 1;
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
		{
			exec_child(ms, partition->cmds, fd, i, &tmp);
		}
		else
		{
			if (tmp > 0)
				close(tmp);
			if ((i != (ms->nb_pipes + 1)) && ms->nb_pipes)
				tmp = dup(fd[0]);
			close_fds(fd);
		}	
		i++;
		partition = partition->next;
	}
	return (wait_children(ms));
}

int	exec(t_minishell *ms)
{
	//lancer les heredoc avant tout
	if(!here_doc(ms))
		return (0);
	//Si commande simple + builtin
	if (!ms->nb_pipes && is_builtin(ms->partition->cmds))
	{
		if (exec_single_builtin(ms) == -1)
			return (0);
	}
	else
		g_status = exec2(ms);
	//le mettre dans un processus enfant pour pas qu'il exit 
	return (1);
}
