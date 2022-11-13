/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:59:54 by skhali            #+#    #+#             */
/*   Updated: 2022/11/05 14:57:46 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quotes(char *str)
{
	int		i;
	char	del;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			del = str[i];
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
			while (str[i] && str[i] != del)
				i++;
			if (str[i] == del)
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
		}
		else
			i++;
	}
	return (str);
}

char	*get_filename(void)
{
	char	*filename;
	int		i;
	char	*i_char;

	i = 0;
	while (1)
	{
		i_char = ft_itoa(i);
		if (!i_char)
			return (NULL);
		filename = ft_strjoin("/tmp/heredoc", i_char);
		if (!filename)
			return (free(i_char), NULL);
		free(i_char);
		if (!(access(filename, 0) == 0))
			return (filename);
		free(filename);
		i++;
	}
	return (NULL);
}

int	create_hd(t_command **cmd)
{
	t_heredoc	*hd;
	char		*limit;
	char		*tmp;

	hd = malloc(sizeof(t_heredoc));
	if (!hd)
		return (0);
	limit = ft_strdup((*cmd)->cmds);
	hd->file = ft_strdup("");
	hd->filename = "";
	handle_signals_heredoc();
	while (1)
	{
		tmp = readline(">");
		if (!tmp)
			return (free(limit), free(hd->file), free(hd), 0);
		if (!ft_strcmp(limit, tmp))
			break ;
		hd->file = ft_strjoinms(hd->file, tmp);
		free(tmp);
	}
	return (free(tmp), free(limit), (*cmd)->hd = hd, 1);
}

int	here_doc_boucle(t_command **cmd, int *fd2, int *fd)
{
	if (!create_hd(cmd))
	{
		if (g_status == -42)
			return (g_status = 130, dup2(*fd2, 0), close(*fd2),
				handle_signals(), 0);
		return (close(*fd2), handle_signals(), 0);
	}
	handle_signals();
	(*cmd)->hd->filename = get_filename();
	if (!(*cmd)->hd->filename)
		return (free((*cmd)->hd), close(*fd2), 0);
	*fd = open((*cmd)->hd->filename, O_CREAT | O_RDWR | O_TRUNC,
			0000644);
	if (*fd < 0)
		return (free((*cmd)->hd), close(*fd), close(*fd2), 0);
	write(*fd, (*cmd)->hd->file, ft_strlen((*cmd)->hd->file));
	close(*fd);
	return (1);
}

int	here_doc(t_minishell *ms)
{
	t_command	*cmd;
	t_partition	*partition;
	int			fd;
	int			fd2;

	partition = ms->partition;
	fd2 = dup(0);
	while (partition)
	{
		cmd = partition->cmds;
		while (cmd)
		{
			if (cmd->id == 10)
			{
				if (!here_doc_boucle(&cmd, &fd2, &fd))
					return (0);
			}
			else
				cmd->hd = NULL;
			cmd = cmd->next;
		}
		partition = partition->next;
	}
	return (close(fd2), 1);
}
